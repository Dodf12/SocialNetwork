PRAGMA foreign_keys = ON;

-- USERS
CREATE TABLE IF NOT EXISTS users (
  id            INTEGER PRIMARY KEY AUTOINCREMENT,
  username      TEXT NOT NULL UNIQUE,
  birthYear    INTEGER NOT NULL,
  zipCode       INTEGER NOT NULL,
  friendsList  INTEGER[] DEFAULT '{}',
  created_at    TEXT NOT NULL DEFAULT (datetime('now')),
  updated_at    TEXT NOT NULL DEFAULT (datetime('now'))
);

-- POSTS
CREATE TABLE IF NOT EXISTS posts (
  postId         INTEGER PRIMARY KEY AUTOINCREMENT,
  message   TEXT NOT NULL,
  profileId    INTEGER NOT NULL,
  authorId    INTEGER NOT NULL,
  likes     INTEGER DEFAULT 0,
  visibility TEXT NOT NULL DEFAULT 'PUBLIC'
    CHECK (visibility IN ('PUBLIC','FRIENDS','PRIVATE')),
  created_at TEXT NOT NULL DEFAULT (datetime('now')),
  FOREIGN KEY (profileId) REFERENCES users(id) ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_posts_profileId ON posts(profileId);

-- BIOS
CREATE TABLE IF NOT EXISTS bios (
  user_id INTEGER PRIMARY KEY,
  bio     TEXT NOT NULL,
  FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

INSERT OR IGNORE INTO users (username, birthYear, zipCode) VALUES
  ('alice', 1990, 12345),
  ('bob', 1985, 67890),
  ('charlie', 1992, 54321);


