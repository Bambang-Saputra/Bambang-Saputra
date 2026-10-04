// Generates the pixel village banner (day + night) and one icon per building.
// Run: node scripts/village.mjs  ->  writes into assets/
// The field in the banner is drawn from data/contributions.json, which
// scripts/fetch-contributions.mjs refreshes every day (see .github/workflows).
import { writeFileSync, mkdirSync, readFileSync, existsSync } from "node:fs";
import { fileURLToPath } from "node:url";
import { dirname, join } from "node:path";

const OUT = join(dirname(fileURLToPath(import.meta.url)), "..", "assets");
mkdirSync(OUT, { recursive: true });

// Without the data file (first run, offline) the field falls back to a seeded pattern.
const DATA_FILE = join(dirname(fileURLToPath(import.meta.url)), "..", "data", "contributions.json");
const CONTRIB = existsSync(DATA_FILE) ? JSON.parse(readFileSync(DATA_FILE, "utf8")) : null;

// ---------- palettes ----------
const THEMES = {
  day: {
    sky: ["#4f9bd6", "#62a8dd", "#78b5e3", "#8fc2e8", "#a8d0ec"],
    sun: "#ffd166", sunEdge: "#f4a940",
    cloud: "#ffffff", cloudShade: "#e3f0f7",
    hillFar: "#86b39a", hillNear: "#5d9a5a",
    grass: "#4e9440", grassDark: "#437f36", path: "#dcb57a", pathDark: "#b8925c",
    soil: "#9a7349", soilBed: "#6e4f32", crops: ["#9be9a8", "#40c463", "#30a14e", "#216e39"],
    outline: "#3a2a22",
    ink: "#1d2b45", inkShadow: "#ffffff",
    window: "#cfe8f6", windowLit: "#cfe8f6", windowFrame: "#5a4636",
    door: "#6b4429", trunk: "#7a5232", leaf: "#4f8f3e", leafLight: "#69a952",
    smoke: "#ffffff",
  },
  night: {
    sky: ["#0d1630", "#132042", "#1a2a52", "#22345f", "#2c3f6b"],
    sun: "#f3efd9", sunEdge: "#c9c4a8",
    cloud: "#2f3f69", cloudShade: "#28375e",
    hillFar: "#1f3b3a", hillNear: "#1a3330",
    grass: "#21402d", grassDark: "#1b3626", path: "#5b4a3a", pathDark: "#4c3d30",
    soil: "#3a2e27", soilBed: "#2a211c", crops: ["#0e4429", "#006d32", "#26a641", "#39d353"],
    outline: "#0a0e18",
    ink: "#f6e7c8", inkShadow: "#0a1124",
    window: "#3a4566", windowLit: "#ffcf5c", windowFrame: "#2a2019",
    door: "#2e1f15", trunk: "#3d2a1c", leaf: "#1d3d2c", leafLight: "#25503a",
    smoke: "#8a93ad",
  },
};

// Product colours are reused from the real projects (see portfolio design notes).
const BUILDINGS = {
  home:    { day: { wall: "#ecdcb8", roof: "#8a5634" }, night: { wall: "#8f8166", roof: "#4a2e1c" } },
  kitchen: { day: { wall: "#f6eee0", roof: "#9e4526", awning: "#c8553d" }, night: { wall: "#a5977f", roof: "#5a2715", awning: "#7a3324" } },
  school:  { day: { wall: "#ebe4d2", roof: "#0a6156", bell: "#e8b23a" }, night: { wall: "#8c8775", roof: "#073b35", bell: "#b58a2c" } },
  library: { day: { wall: "#dcd6c8", roof: "#5f7186", column: "#f7f4ec" }, night: { wall: "#7d786c", roof: "#323c49", column: "#a39f94" } },
  clinic:  { day: { wall: "#f7f7f5", roof: "#b9c3cc", cross: "#c0392b" }, night: { wall: "#9da0a3", roof: "#5b6168", cross: "#d9483a" } },
  quest:   { day: { wood: "#9a6334", board: "#b8794a", paper: "#f6ecd0", pin: "#c0392b" }, night: { wood: "#4f3320", board: "#5e3d24", paper: "#b9ae92", pin: "#d9483a" } },
  books:   { day: { wall: "#6e5a96", roof: "#3f305c" }, night: { wall: "#3f345a", roof: "#221a36" } },
  shed:    { day: { wall: "#a8743f", plank: "#8a5c30", roof: "#5e3b22", dark: "#2e1f15", handle: "#c9a26a", metal: "#a9b4bf" }, night: { wall: "#5a3f24", plank: "#4a331d", roof: "#2f1e12", dark: "#140d08", handle: "#7a6240", metal: "#6b7480" } },
  cinema:  { day: { wall: "#36324a", roof: "#221f30", marquee: "#f2efe6", bulb: "#f4b43c", poster: "#c8553d" }, night: { wall: "#221f30", roof: "#14121d", marquee: "#d8d3c4", bulb: "#ffd36b", poster: "#a23d2c" } },
};

// ---------- tiny pixel font (5x7) ----------
const FONT = {
  A: ["01110","10001","10001","11111","10001","10001","10001"],
  B: ["11110","10001","10001","11110","10001","10001","11110"],
  C: ["01111","10000","10000","10000","10000","10000","01111"],
  D: ["11110","10001","10001","10001","10001","10001","11110"],
  E: ["11111","10000","10000","11110","10000","10000","11111"],
  G: ["01111","10000","10000","10011","10001","10001","01111"],
  I: ["11111","00100","00100","00100","00100","00100","11111"],
  M: ["10001","11011","10101","10101","10001","10001","10001"],
  N: ["10001","11001","10101","10011","10001","10001","10001"],
  O: ["01110","10001","10001","10001","10001","10001","01110"],
  P: ["11110","10001","10001","11110","10000","10000","10000"],
  R: ["11110","10001","10001","11110","10100","10010","10001"],
  S: ["01111","10000","10000","01110","00001","00001","11110"],
  T: ["11111","00100","00100","00100","00100","00100","00100"],
  U: ["10001","10001","10001","10001","10001","10001","01110"],
  F: ["11111","10000","10000","11110","10000","10000","10000"],
  K: ["10001","10010","10100","11000","10100","10010","10001"],
  L: ["10000","10000","10000","10000","10000","10000","11111"],
  "·": ["00000","00000","00000","01100","01100","00000","00000"],
  " ": ["00000","00000","00000","00000","00000","00000","00000"],
};

// ---------- drawing primitives ----------
function canvas() {
  const rects = [];
  const r = (x, y, w, h, fill, cls) => rects.push({ x, y, w, h, fill, cls });
  return { rects, r };
}

function text(c, str, x, y, scale, fill) {
  let cx = x;
  for (const ch of str) {
    const g = FONT[ch];
    g.forEach((row, gy) =>
      [...row].forEach((bit, gx) => {
        if (bit === "1") c.r(cx + gx * scale, y + gy * scale, scale, scale, fill);
      }),
    );
    cx += 6 * scale;
  }
}

function mulberry(seed) {
  return () => {
    seed |= 0; seed = (seed + 0x6d2b79f5) | 0;
    let t = Math.imul(seed ^ (seed >>> 15), 1 | seed);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

// Stepped roof: two cells in per row, one cell overhang.
function roof(c, x, w, wallTop, fill) {
  const rh = Math.ceil((w + 2) / 4);
  for (let i = 0; i < rh; i++) {
    const inset = 2 * (rh - 1 - i);
    c.r(x - 1 + inset, wallTop - rh + i, w + 2 - 2 * inset, 1, fill);
  }
  return wallTop - rh;
}

function win(c, t, x, y, w, h, lit) {
  c.r(x - 1, y - 1, w + 2, h + 2, t.windowFrame);
  c.r(x, y, w, h, lit ? t.windowLit : t.window);
  if (w >= 3) c.r(x + Math.floor(w / 2), y, 1, h, t.windowFrame);
}

function tree(c, t, x, gy) {
  c.r(x + 3, gy - 4, 2, 4, t.trunk);
  c.r(x + 1, gy - 11, 6, 7, t.leaf);
  c.r(x, gy - 9, 8, 4, t.leaf);
  c.r(x + 2, gy - 12, 4, 1, t.leaf);
  c.r(x + 2, gy - 10, 2, 2, t.leafLight);
}

// ---------- buildings (bottom edge sits on gy) ----------
const DRAW = {
  shed(c, t, x, gy, night) {
    const p = BUILDINGS.shed[night ? "night" : "day"], w = 14, h = 9;
    c.r(x, gy - h, w, h, p.wall);
    for (const px of [x + 3, x + 7, x + 11]) c.r(px, gy - h, 1, h, p.plank);
    for (let i = 0; i < 4; i++) c.r(x - 1, gy - h - 1 - i, w + 2 - 4 * i, 1, p.roof); // single slope
    c.r(x + 2, gy - 7, 6, 7, p.dark); // open door
    c.r(x + 3, gy - 6, 1, 6, p.handle); // rake inside
    c.r(x + 2, gy - 6, 3, 1, p.metal);
    c.r(x + 6, gy - 5, 1, 5, p.handle); // hoe inside
    c.r(x + 5, gy - 5, 2, 1, p.metal);
    c.r(x + 12, gy - 7, 1, 5, p.handle); // shovel leaning outside
    c.r(x + 11, gy - 2, 3, 2, p.metal);
    return w;
  },
  home(c, t, x, gy, night) {
    const p = BUILDINGS.home[night ? "night" : "day"], w = 14, h = 10;
    c.r(x, gy - h, w, h, p.wall);
    roof(c, x, w, gy - h, p.roof);
    c.r(x + 2, gy - 6, 3, 6, t.door);
    win(c, t, x + 8, gy - 7, 3, 3, night);
    return w;
  },
  kitchen(c, t, x, gy, night) {
    const p = BUILDINGS.kitchen[night ? "night" : "day"], w = 18, h = 11;
    c.r(x + 13, gy - h - 8, 3, 6, p.roof); // chimney
    c.r(x, gy - h, w, h, p.wall);
    roof(c, x, w, gy - h, p.roof);
    win(c, t, x + 3, gy - 8, 6, 3, night);
    for (let i = 0; i < 8; i++) c.r(x + 2 + i, gy - 10, 1, 2, i % 2 ? p.wall : p.awning); // striped awning
    c.r(x + 12, gy - 7, 4, 7, t.door);
    return w;
  },
  school(c, t, x, gy, night) {
    const p = BUILDINGS.school[night ? "night" : "day"], w = 20, h = 12;
    c.r(x, gy - h, w, h, p.wall);
    const top = roof(c, x, w, gy - h, p.roof);
    c.r(x + 8, top - 6, 4, 6, p.wall); // bell tower
    c.r(x + 7, top - 7, 6, 1, p.roof);
    c.r(x + 8, top - 8, 4, 1, p.roof);
    c.r(x + 9, top - 4, 2, 2, p.bell);
    win(c, t, x + 2, gy - 9, 3, 3, night);
    win(c, t, x + 15, gy - 9, 3, 3, night);
    c.r(x + 8, gy - 7, 4, 7, t.door);
    c.r(x + 10, gy - 7, 1, 7, t.windowFrame);
    return w;
  },
  library(c, t, x, gy, night) {
    const p = BUILDINGS.library[night ? "night" : "day"], w = 22, h = 11;
    c.r(x, gy - h, w, h, p.wall);
    c.r(x - 1, gy - h - 1, w + 2, 1, p.roof);
    for (let i = 0; i < 4; i++) c.r(x - 1 + 2 * i, gy - h - 2 - i, w + 2 - 4 * i, 1, p.roof); // low pediment
    for (const cx of [x + 1, x + 6, x + 15, x + 20]) c.r(cx, gy - h + 1, 1, h - 2, p.column);
    win(c, t, x + 3, gy - 8, 1, 4, night);
    win(c, t, x + 17, gy - 8, 1, 4, night);
    c.r(x + 9, gy - 7, 4, 6, t.door);
    c.r(x - 1, gy - 1, w + 2, 1, p.column); // steps
    return w;
  },
  clinic(c, t, x, gy, night) {
    const p = BUILDINGS.clinic[night ? "night" : "day"], w = 18, h = 12;
    c.r(x, gy - h, w, h, p.wall);
    c.r(x - 1, gy - h - 2, w + 2, 2, p.roof);
    c.r(x + 8, gy - h + 1, 2, 6, p.cross);
    c.r(x + 6, gy - h + 3, 6, 2, p.cross);
    win(c, t, x + 2, gy - 8, 3, 3, night);
    win(c, t, x + 13, gy - 8, 3, 3, night);
    c.r(x + 7, gy - 5, 4, 5, t.door);
    return w;
  },
  quest(c, t, x, gy, night) {
    const p = BUILDINGS.quest[night ? "night" : "day"], w = 14;
    c.r(x + 1, gy - 12, 2, 12, p.wood);
    c.r(x + 11, gy - 12, 2, 12, p.wood);
    c.r(x - 1, gy - 14, w + 2, 2, p.wood); // little roof
    c.r(x, gy - 12, w, 7, p.board);
    c.r(x + 2, gy - 11, 3, 3, p.paper);
    c.r(x + 6, gy - 11, 2, 4, p.paper);
    c.r(x + 9, gy - 10, 3, 3, p.paper);
    c.r(x + 3, gy - 11, 1, 1, p.pin);
    c.r(x + 10, gy - 10, 1, 1, p.pin);
    return w;
  },
  books(c, t, x, gy, night) {
    const p = BUILDINGS.books[night ? "night" : "day"], w = 18, h = 12;
    c.r(x, gy - h, w, h, p.wall);
    roof(c, x, w, gy - h, p.roof);
    c.r(x + 2, gy - 9, 9, 6, t.windowFrame);
    const spines = ["#e85d75", "#f2c14e", "#5fb3d9", "#7bc67e", "#f08a4b", "#b38ee8", "#e85d75", "#5fb3d9", "#f2c14e"];
    spines.forEach((s, i) => c.r(x + 2 + i, gy - 8 + (i % 3 === 1 ? 1 : 0), 1, i % 3 === 1 ? 4 : 5, night ? dim(s) : s));
    c.r(x + 13, gy - 7, 3, 7, t.door);
    return w;
  },
  cinema(c, t, x, gy, night) {
    const p = BUILDINGS.cinema[night ? "night" : "day"], w = 22, h = 15;
    c.r(x, gy - h, w, h, p.wall);
    c.r(x - 1, gy - h - 1, w + 2, 1, p.roof);
    c.r(x + 1, gy - h + 2, w - 2, 3, p.marquee);
    for (let i = 0; i < 10; i++) c.r(x + 2 + 2 * i, gy - h + 1, 1, 1, p.bulb, i % 2 ? "blink-a" : "blink-b");
    for (let i = 0; i < 10; i++) c.r(x + 2 + 2 * i, gy - h + 5, 1, 1, p.bulb, i % 2 ? "blink-b" : "blink-a");
    c.r(x + 2, gy - 8, 4, 6, p.poster);
    c.r(x + 16, gy - 8, 4, 6, night ? "#2f5d7a" : "#3f7fa6");
    c.r(x + 8, gy - 7, 6, 7, t.door);
    c.r(x + 11, gy - 7, 1, 7, t.windowFrame);
    return w;
  },
};

function dim(hex) {
  const n = parseInt(hex.slice(1), 16);
  const f = (v) => Math.round(v * 0.55).toString(16).padStart(2, "0");
  return `#${f(n >> 16)}${f((n >> 8) & 255)}${f(n & 255)}`;
}

// Draws into a scratch canvas, then adds a one-cell dark outline around the
// silhouette. The outline is what separates sprites from the background.
function outlined(c, color, draw, floorY = Infinity, cls) {
  const tmp = canvas();
  draw(tmp);
  const occ = new Set();
  for (const q of tmp.rects) {
    if (q.cls && q.cls.startsWith("smoke")) continue;
    for (let yy = Math.floor(q.y); yy < Math.ceil(q.y + q.h); yy++)
      for (let xx = Math.floor(q.x); xx < Math.ceil(q.x + q.w); xx++) occ.add(`${xx},${yy}`);
  }
  const edge = new Set();
  for (const key of occ) {
    const [x, y] = key.split(",").map(Number);
    for (const [dx, dy] of [[1, 0], [-1, 0], [0, 1], [0, -1]]) {
      const k = `${x + dx},${y + dy}`;
      if (!occ.has(k) && y + dy < floorY) edge.add(k);
    }
  }
  for (const k of edge) {
    const [x, y] = k.split(",").map(Number);
    c.r(x, y, 1, 1, color, cls);
  }
  c.rects.push(...tmp.rects);
}

// Two frames: hoe raised, hoe in the ground. CSS swaps them.
const FARMER = {
  a: [
    "...hhhh....mm.",
    "..hhhhhh...mw.",
    ".hhHHHHhh..w..",
    "...ssss...w...",
    "...sses..w....",
    "...ssss.w.....",
    "..ccccccw.....",
    ".ccccccss.....",
    ".cccccc.......",
    ".cccccc.......",
    "..CCCC........",
    "..pppp........",
    "..pp.pp.......",
    "..pp.pp.......",
    ".bbb.bbb......",
  ],
  b: [
    "...hhhh.......",
    "..hhhhhh......",
    ".hhHHHHhh.....",
    "...ssss.......",
    "...sses.......",
    "...ssss.......",
    "..cccccc......",
    ".cccccccssw...",
    ".cccccc...w...",
    ".cccccc....w..",
    "..CCCC......w.",
    "..pppp......w.",
    "..pp.pp.....mm",
    "..pp.pp.....mm",
    ".bbb.bbb......",
  ],
  // Walking, hoe held upright.
  w1: [
    "...hhhh..mmm..",
    "..hhhhhh.wm...",
    ".hhHHHHhhw....",
    "...ssss..w....",
    "...sses..w....",
    "...ssss..w....",
    "..cccccc.w....",
    ".ccccccssw....",
    ".cccccc..w....",
    ".cccccc..w....",
    "..CCCC...w....",
    "..pppp...w....",
    "..pp.pp.......",
    ".pp...pp......",
    ".bb...bb......",
  ],
  w2: [
    "...hhhh..mmm..",
    "..hhhhhh.wm...",
    ".hhHHHHhhw....",
    "...ssss..w....",
    "...sses..w....",
    "...ssss..w....",
    "..cccccc.w....",
    ".ccccccssw....",
    ".cccccc..w....",
    ".cccccc..w....",
    "..CCCC...w....",
    "..pppp...w....",
    "..pp.pp.......",
    "..pp.pp.......",
    ".bbb.bbb......",
  ],
};

function farmer(c, x, y, night, outline, frames = ["a", "b"]) {
  const k = night
    ? { h: "#a58c45", H: "#6e2f1e", s: "#b88a6a", e: "#1a120c", c: "#355a8c", C: "#264468", p: "#3e3226", b: "#1f1712", w: "#5e4126", m: "#7d8792" }
    : { h: "#efc957", H: "#a5462b", s: "#e8a87f", e: "#2b1d14", c: "#3f7fc4", C: "#2f639c", p: "#6b4f36", b: "#3b2a20", w: "#8a5a2c", m: "#a9b4bf" };
  for (const f of frames) {
    outlined(c, outline, (o) =>
      FARMER[f].forEach((row, yy) => [...row].forEach((ch, xx) => { if (k[ch]) o.r(x + xx, y + yy, 1, 1, k[ch], `frame-${f}`); })),
      Infinity, `frame-${f}`);
  }
}

// ---------- svg output ----------
function svg(c, W, H, P, title, extraCss = "") {
  const body = c.rects
    .map(({ x, y, w, h, fill, cls }) => `<rect x="${x}" y="${y}" width="${w}" height="${h}" fill="${fill}"${cls ? ` class="${cls}"` : ""}/>`)
    .join("");
  const css = `
.twinkle{animation:tw 3.2s ease-in-out infinite}.twinkle.d2{animation-delay:-1.1s}.twinkle.d3{animation-delay:-2.3s}
@keyframes tw{0%,100%{opacity:1}50%{opacity:.25}}
.smoke{animation:sm 4s linear infinite;opacity:0}.smoke.d2{animation-delay:-1.33s}.smoke.d3{animation-delay:-2.66s}
@keyframes sm{0%{transform:translate(0,0);opacity:.0}15%{opacity:.8}100%{transform:translate(3px,-9px);opacity:0}}
.drift{animation:dr 40s ease-in-out infinite alternate}
@keyframes dr{from{transform:translateX(0)}to{transform:translateX(14px)}}
.blink-a{animation:bl 1.2s steps(1) infinite}.blink-b{animation:bl 1.2s steps(1) infinite;animation-delay:-.6s}
@keyframes bl{0%{opacity:1}50%{opacity:.35}}
.frame-a{animation:fa 1.4s steps(1) infinite}.frame-b{opacity:0;animation:fb 1.4s steps(1) infinite}
@keyframes fa{0%{opacity:1}50%{opacity:0}}@keyframes fb{0%{opacity:0}50%{opacity:1}}
.frame-w1{animation:fa .5s steps(1) infinite}.frame-w2{opacity:0;animation:fb .5s steps(1) infinite}
${extraCss}
@media (prefers-reduced-motion:reduce){*{animation:none!important}.smoke{opacity:.6}}`;
  return `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 ${W} ${H}" width="${W * P}" height="${H * P}" shape-rendering="crispEdges" role="img"><title>${title}</title><style>${css}</style>${body}</svg>\n`;
}

// ---------- contribution field ----------
// Returns weeks of seven levels (0 = none, 1-4 = GitHub's quartiles, null = no
// such day, e.g. the rest of the current week).
function fieldWeeks(rand) {
  if (CONTRIB) return CONTRIB.weeks;
  return Array.from({ length: 53 }, (_, w) =>
    Array.from({ length: 7 }, (_, d) => {
      if (w === 52 && d > 3) return null;
      const v = rand();
      return v < 0.55 ? 0 : v < 0.75 ? 1 : v < 0.88 ? 2 : v < 0.96 ? 3 : 4;
    }),
  );
}

// ---------- banner ----------
const LAYOUT = [
  ["home", 10], ["kitchen", 30], ["school", 55], ["library", 82],
  ["clinic", 112], ["quest", 137], ["books", 158], ["cinema", 183], ["shed", 210],
];

function banner(mode) {
  const night = mode === "night";
  const t = THEMES[mode];
  const W = 240, H = 88, GY = 60;
  const c = canvas();
  const rand = mulberry(7);

  // sky bands
  const bandH = Math.ceil(GY / t.sky.length);
  t.sky.forEach((col, i) => c.r(0, i * bandH, W, bandH + 1, col));

  if (night) {
    for (let i = 0; i < 55; i++) {
      const x = Math.floor(rand() * W), y = Math.floor(rand() * 40);
      if (x < 196 && y < 34) continue; // keep the name area calm
      c.r(x, y, 1, 1, "#f6efd2", `twinkle d${1 + (i % 3)}`);
    }
    for (let i = 0; i < 18; i++) {
      const x = 4 + Math.floor(rand() * 190), y = 34 + Math.floor(rand() * 6);
      c.r(x, y, 1, 1, "#f6efd2", `twinkle d${1 + (i % 3)}`);
    }
    // crescent moon
    c.r(212, 7, 6, 1, t.sun); c.r(210, 8, 9, 2, t.sun); c.r(209, 10, 9, 5, t.sun);
    c.r(210, 15, 9, 2, t.sun); c.r(212, 17, 6, 1, t.sun);
    c.r(214, 8, 6, 9, t.sky[0]); c.r(213, 9, 7, 7, t.sky[0]);
  } else {
    c.r(210, 6, 8, 1, t.sunEdge); c.r(208, 7, 12, 2, t.sun); c.r(207, 9, 14, 6, t.sun);
    c.r(208, 15, 12, 2, t.sun); c.r(210, 17, 8, 1, t.sunEdge);
    for (const [cx, cy] of [[203, 27], [120, 35]]) {
      c.rects.push({ g: "open" });
      c.r(cx, cy, 14, 3, t.cloud); c.r(cx + 3, cy - 2, 7, 2, t.cloud); c.r(cx + 2, cy + 3, 12, 1, t.cloudShade);
      c.rects.push({ g: "close" });
    }
  }

  // name + subline
  text(c, "BAMBANG SAPUTRA", 9, 7, 2, t.inkShadow);
  text(c, "BAMBANG SAPUTRA", 8, 6, 2, t.ink);
  text(c, "COMPUTER SCIENCE · BINUS BANDUNG", 8, 24, 1, t.ink);

  // hills
  for (let x = 0; x < W; x++) {
    const far = Math.round(42 + 3 * Math.sin(x / 15) + 2 * Math.sin(x / 6.1 + 1));
    c.r(x, far, 1, GY - far, t.hillFar);
    const near = Math.round(50 + 2 * Math.sin(x / 9 + 2) + 1.5 * Math.sin(x / 4.3));
    c.r(x, near, 1, GY - near, t.hillNear);
  }

  // ground + path
  c.r(0, GY, W, H - GY, t.grass);
  c.r(0, GY, W, 2, t.path);
  c.r(0, GY + 2, W, 1, t.pathDark);
  for (let i = 0; i < 70; i++) c.r(Math.floor(rand() * W), GY + 4 + Math.floor(rand() * (H - GY - 4)), 1, 1, t.grassDark);

  // trees behind the street
  for (const x of [1, 48, 74, 131, 228]) outlined(c, t.outline, (o) => tree(o, t, x, GY), GY);

  // buildings
  for (const [name, x] of LAYOUT) {
    outlined(c, t.outline, (o) => DRAW[name](o, t, x, GY, night), GY);
    if (name === "kitchen") for (const d of [1, 2, 3]) c.r(x + 14, GY - 11 - 9, 2, 2, t.smoke, `smoke d${d}`);
  }

  // lamp posts
  for (const x of [52, 109, 180]) {
    c.r(x, GY - 9, 1, 9, night ? "#11151f" : "#3b3f4a");
    c.r(x - 1, GY - 10, 3, 1, night ? "#11151f" : "#3b3f4a");
    c.r(x - 1, GY - 9, 3, 2, night ? "#ffd36b" : "#f3e7b5");
  }

  // The field is the real contribution calendar: one column per week, one row
  // per weekday, in GitHub's own four greens. The farmer walks the year from
  // left to right; each week's crops are re-planted as he passes, and he ends
  // the loop hoeing today's column. With animation off he just stands there.
  const weeks = fieldWeeks(rand);
  const N = weeks.length, pitch = 3, fx = 8, fy = GY + 5;
  const T = 28, WALK = 0.78, D = (N - 1) * pitch;
  c.r(fx - 2, fy - 2, N * pitch + 2, 7 * pitch + 2, t.soilBed);
  weeks.forEach((days, i) => {
    days.forEach((lvl, d) => { if (lvl !== null) c.r(fx + i * pitch, fy + d * pitch, 2, 2, t.soil); });
    const reach = (Math.min(i + 1, N - 1) / (N - 1)) * WALK * T;
    c.rects.push({ g: "open", cls: "col", style: `animation-delay:${(reach - T).toFixed(2)}s` });
    days.forEach((lvl, d) => { if (lvl > 0) c.r(fx + i * pitch, fy + d * pitch, 2, 2, t.crops[lvl - 1]); });
    c.rects.push({ g: "close" });
  });

  const baseX = fx + (N - 1) * pitch - 12, baseY = fy - 15;
  c.rects.push({ g: "open", cls: "walker" }, { g: "open", cls: "fade" }, { g: "open", cls: "walking" });
  farmer(c, baseX, baseY, night, t.outline, ["w1", "w2"]);
  c.rects.push({ g: "close" }, { g: "open", cls: "hoeing" });
  farmer(c, baseX, baseY, night, t.outline, ["a", "b"]);
  c.rects.push({ g: "close" }, { g: "close" }, { g: "close" });

  const fieldCss = `
.col{animation:grow ${T}s infinite}
@keyframes grow{0%{opacity:0}.6%{opacity:1}97.5%{opacity:1}98%{opacity:0}100%{opacity:0}}
.walker{animation:walk ${T}s infinite}
@keyframes walk{0%{transform:translateX(-${D}px);animation-timing-function:steps(${D},end)}${WALK * 100}%,100%{transform:translateX(0)}}
.fade{animation:fade ${T}s infinite}
@keyframes fade{0%{opacity:0}1.5%{opacity:1}97%{opacity:1}100%{opacity:0}}
.walking{opacity:0;animation:walking ${T}s steps(1) infinite}
@keyframes walking{0%{opacity:1}${WALK * 100}%{opacity:0}100%{opacity:0}}
.hoeing{animation:hoeing ${T}s steps(1) infinite}
@keyframes hoeing{0%{opacity:0}${WALK * 100}%{opacity:1}100%{opacity:1}}`;

  // flowers to the right of the field
  for (let i = 0; i < 16; i++) {
    const x = fx + N * pitch + 4 + Math.floor(rand() * (W - fx - N * pitch - 8)), y = GY + 5 + Math.floor(rand() * (H - GY - 8));
    c.r(x, y, 1, 1, ["#f28fad", "#ffd166", "#ffffff"][i % 3]);
  }

  return svgWithGroups(c, W, H, 4, night
    ? "Pixel art of a small village at night with Bambang Saputra's name in the sky. In front of the buildings is a field planted from his real GitHub contributions over the past year, tended by a farmer."
    : "Pixel art of a small village by day with Bambang Saputra's name in the sky. In front of the buildings is a field planted from his real GitHub contributions over the past year, tended by a farmer.", fieldCss);
}

// patch svg() to understand group markers
const _svg = svg;
function svgWithGroups(c, W, H, P, title, extraCss = "") {
  const parts = [];
  for (const r of c.rects) {
    if (r.g === "open") parts.push(`<g class="${r.cls || "drift"}"${r.style ? ` style="${r.style}"` : ""}>`);
    else if (r.g === "close") parts.push("</g>");
    else parts.push(`<rect x="${r.x}" y="${r.y}" width="${r.w}" height="${r.h}" fill="${r.fill}"${r.cls ? ` class="${r.cls}"` : ""}/>`);
  }
  const shell = _svg({ rects: [] }, W, H, P, title, extraCss);
  return shell.replace("</svg>", parts.join("") + "</svg>");
}

// ---------- icons ----------
function icon(name, mode) {
  const night = mode === "night";
  const t = THEMES[mode];
  const S = 32, GY = 28;
  const c = canvas();
  // Transparent background: the outline keeps the building readable on both
  // GitHub themes, and the icon no longer reads as a dark square in dark mode.
  c.r(0, GY, S, S - GY, t.grass);
  c.r(0, GY, S, 1, t.path);
  if (name === "field") {
    const rand = mulberry(3);
    c.r(1, 11, 17, 15, t.soilBed);
    for (let cy = 0; cy < 5; cy++)
      for (let cx = 0; cx < 5; cx++) {
        const v = rand();
        const lvl = v < 0.25 ? -1 : v < 0.5 ? 0 : v < 0.72 ? 1 : v < 0.88 ? 2 : 3;
        c.r(2 + cx * 3, 12 + cy * 3, 2, 2, lvl < 0 ? t.soil : t.crops[lvl]);
      }
    farmer(c, 17, GY - 14, night, t.outline);
  } else if (name === "hobbies") {
    outlined(c, t.outline, (o) => DRAW.books(o, t, -5, GY, night), GY);
    outlined(c, t.outline, (o) => DRAW.cinema(o, t, 14, GY, night), GY);
  } else {
    const widths = { shed: 14, home: 14, kitchen: 18, school: 20, library: 22, clinic: 18, quest: 14, books: 18, cinema: 22 };
    const x = Math.floor((S - widths[name]) / 2);
    outlined(c, t.outline, (o) => DRAW[name](o, t, x, GY, night), GY);
    if (name === "kitchen") for (const d of [1, 2, 3]) c.r(x + 14, GY - 20, 2, 2, t.smoke, `smoke d${d}`);
  }
  return svgWithGroups(c, S, S, 3, `Pixel art ${name}`);
}

// ---------- contact buttons ----------
// Chunky pixel buttons so the contact links read as buttons, not as fine print.
// The LinkedIn mark is deliberately not drawn (its owner asked icon sets to
// drop it); a briefcase stands in, the same call the portfolio made.
const GLYPH = {
  home:     ["...#...", "..###..", ".#####.", "#######", ".##.##.", ".##.##.", ".#####."],
  case:     ["..###..", "..#.#..", "#######", "#######", "#.....#", "#######", "#######"],
  envelope: ["#######", "##...##", "#.#.#.#", "#..#..#", "#.....#", "#.....#", "#######"],
};
const BUTTONS = [
  { file: "btn-portfolio", label: "PORTFOLIO", glyph: "home",     base: "#1f5f4e", light: "#2f7d67", dark: "#123a30" },
  { file: "btn-linkedin",  label: "LINKEDIN",  glyph: "case",     base: "#0a66c2", light: "#2a83db", dark: "#064585" },
  { file: "btn-email",     label: "EMAIL",     glyph: "envelope", base: "#c8553d", light: "#dd705a", dark: "#8a3524" },
];

function button({ label, glyph, base, light, dark }) {
  const textW = label.length * 6 - 1;
  const W = 1 + 3 + 7 + 3 + textW + 4 + 1, H = 15;
  const c = canvas();
  c.r(1, 0, W - 2, H - 1, dark);       // outline, corners cut
  c.r(0, 1, W, H - 3, dark);
  c.r(1, 1, W - 2, H - 3, base);       // face
  c.r(1, 1, W - 2, 1, light);          // top highlight
  c.r(1, H - 2, W - 2, 1, dark);       // pressed-in bottom edge
  GLYPH[glyph].forEach((row, y) => [...row].forEach((ch, x) => { if (ch === "#") c.r(4 + x, 4 + y, 1, 1, "#ffffff"); }));
  text(c, label, 15, 5, 1, dark);      // drop shadow
  text(c, label, 14, 4, 1, "#ffffff");
  return svgWithGroups(c, W, H, 3, label.charAt(0) + label.slice(1).toLowerCase());
}

for (const b of BUTTONS) writeFileSync(join(OUT, `${b.file}.svg`), button(b));

for (const mode of ["day", "night"]) {
  const b = banner(mode);
  writeFileSync(join(OUT, `village-${mode}.svg`), b);
  for (const n of ["kitchen", "school", "library", "clinic", "quest", "home", "hobbies", "field", "shed"]) {
    writeFileSync(join(OUT, `${n}-${mode}.svg`), icon(n, mode));
  }
}
console.log("done");
