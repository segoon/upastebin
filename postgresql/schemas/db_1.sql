DROP SCHEMA IF EXISTS upastebin CASCADE;

CREATE SCHEMA IF NOT EXISTS upastebin;

CREATE TABLE IF NOT EXISTS upastebin.texts (
    uuid TEXT PRIMARY KEY,
    author TEXT NOT NULL,
    ip_source TEXT NOT NULL,
    text TEXT NOT NULL,
    created_at TIMESTAMPTZ NOT NULL
);
