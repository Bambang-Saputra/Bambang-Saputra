// Turns the tech logos into pixel tiles: assets/tech-<id>.svg.
// The shapes come from Simple Icons (CC0), the same set the portfolio uses,
// stored in data/tech-icons.json. Each path is rasterised onto its native 24x24 grid,
// so the logo is still recognisable but drawn in the same pixels as the village.
//
// Run locally, not in the daily Action (the tiles never change):
//   SHARP_FROM=<any folder with sharp in node_modules>/ node scripts/tech-icons.mjs
import { readFileSync, writeFileSync } from "node:fs";
import { createRequire } from "node:module";
import { fileURLToPath } from "node:url";
import { dirname, join } from "node:path";

const ROOT = join(dirname(fileURLToPath(import.meta.url)), "..");
const sharp = createRequire(process.env.SHARP_FROM || import.meta.url)("sharp");
const ICONS = JSON.parse(readFileSync(join(ROOT, "data", "tech-icons.json"), "utf8"));

const G = 24, PAD = 3, S = G + PAD * 2; // glyph grid, padding, tile size (cells)

function shade(hex, f) {
  const n = parseInt(hex.slice(1), 16);
  const ch = (v) => Math.max(0, Math.min(255, Math.round(f > 1 ? v + (255 - v) * (f - 1) : v * f)));
  return "#" + [n >> 16, (n >> 8) & 255, n & 255].map((v) => ch(v).toString(16).padStart(2, "0")).join("");
}

function luminance(hex) {
  const n = parseInt(hex.slice(1), 16);
  const lin = (v) => ((v /= 255) <= 0.03928 ? v / 12.92 : ((v + 0.055) / 1.055) ** 2.4);
  return 0.2126 * lin(n >> 16) + 0.7152 * lin((n >> 8) & 255) + 0.0722 * lin(n & 255);
}

for (const [id, { t: title, d, c: brand }] of Object.entries(ICONS)) {
  // Very dark brand colours (pandas) get a light outline so the tile does not
  // vanish on GitHub's dark theme.
  const base = brand;
  const ink = luminance(base) > 0.45 ? "#1b1b1b" : "#ffffff";

  const src = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="${G}" height="${G}"><path d="${d}" fill="#000"/></svg>`;
  const { data } = await sharp(Buffer.from(src)).ensureAlpha().raw().toBuffer({ resolveWithObject: true });

  const rects = [];
  const r = (x, y, w, h, fill) => rects.push(`<rect x="${x}" y="${y}" width="${w}" height="${h}" fill="${fill}"/>`);
  const edge = luminance(base) < 0.03 ? shade(base, 1.45) : shade(base, 0.6);
  r(1, 0, S - 2, S, edge); // outline, corners cut
  r(0, 1, S, S - 2, edge);
  r(1, 1, S - 2, S - 2, base);
  r(1, 1, S - 2, 1, shade(base, 1.25)); // highlight
  r(1, S - 2, S - 2, 1, shade(base, 0.75)); // bottom edge
  for (let y = 0; y < G; y++)
    for (let x = 0; x < G; x++)
      if (data[(y * G + x) * 4 + 3] > 110) r(PAD + x, PAD + y, 1, 1, ink);

  const svg = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 ${S} ${S}" width="${S * 1.5}" height="${S * 1.5}" shape-rendering="crispEdges" role="img"><title>${title}</title>${rects.join("")}</svg>\n`;
  writeFileSync(join(ROOT, "assets", `tech-${id}.svg`), svg);
}
console.log(`wrote ${Object.keys(ICONS).length} tiles`);
