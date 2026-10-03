// Fetches the last year of contributions for the profile owner and writes
// data/contributions.json for village.mjs. Runs daily in GitHub Actions.
// Env: GITHUB_TOKEN (the Actions token is enough), GH_LOGIN (profile owner).
import { writeFileSync, mkdirSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, join } from "node:path";

const login = process.env.GH_LOGIN || "Bambang-Saputra";
const token = process.env.GITHUB_TOKEN;
if (!token) throw new Error("GITHUB_TOKEN is not set");

const query = `query($login: String!) {
  user(login: $login) {
    contributionsCollection {
      contributionCalendar {
        totalContributions
        weeks { contributionDays { date weekday contributionLevel } }
      }
    }
  }
}`;

const res = await fetch("https://api.github.com/graphql", {
  method: "POST",
  headers: { Authorization: `bearer ${token}`, "Content-Type": "application/json", "User-Agent": "village-field" },
  body: JSON.stringify({ query, variables: { login } }),
});
const json = await res.json();
if (!res.ok || json.errors) throw new Error(JSON.stringify(json.errors ?? json));

const LEVEL = { NONE: 0, FIRST_QUARTILE: 1, SECOND_QUARTILE: 2, THIRD_QUARTILE: 3, FOURTH_QUARTILE: 4 };
const cal = json.data.user.contributionsCollection.contributionCalendar;

// One array of seven per week, indexed by weekday (0 = Sunday). Days that do
// not exist yet, like the rest of this week, stay null.
const weeks = cal.weeks.map((w) => {
  const days = Array(7).fill(null);
  for (const d of w.contributionDays) days[d.weekday] = LEVEL[d.contributionLevel];
  return days;
});

const out = join(dirname(fileURLToPath(import.meta.url)), "..", "data");
mkdirSync(out, { recursive: true });
// No timestamp in the file: it only changes when the field does, so the daily
// job makes no commit on days with nothing new.
writeFileSync(join(out, "contributions.json"), JSON.stringify({ login, total: cal.totalContributions, weeks }) + "\n");
console.log(`${login}: ${cal.totalContributions} contributions over ${weeks.length} weeks`);
