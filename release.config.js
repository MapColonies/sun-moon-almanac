let URL = require('url').URL;
let gitlabUrl = new URL(process.env.CI_REPOSITORY_URL).origin;

module.exports = {
  extends: "@semantic-release/gitlab-config",
  repository: process.env.CI_REPOSITORY_URL,
  plugins: [
    "@semantic-release/commit-analyzer",
    "@semantic-release/release-notes-generator",
    "@semantic-release/npm",
    ["@semantic-release/gitlab", {
      gitlabUrl,
    }],
  ]
}
