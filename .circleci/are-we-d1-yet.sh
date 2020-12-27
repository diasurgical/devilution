#!/bin/bash

# based on https://github.com/k3rn31p4nic/travis-ci-discord-webhook

# Only run for commits/builds on master, not for PRs for now
if [[ "$CIRCLE_BRANCH" != "master" ]]; then
  exit
fi

# Webhook URL missing, do nothing
if [ -z "$2" ]; then
  exit
fi

echo -e "[Webhook]: Sending webhook to Discord...\\n";

AUTHOR_NAME="$(git log -1 "$CIRCLE_SHA1" --pretty="%aN")"
COMMITTER_NAME="$(git log -1 "$CIRCLE_SHA1" --pretty="%cN")"
COMMIT_SUBJECT="$(git log -1 "$CIRCLE_SHA1" --pretty="%s")"
COMMIT_MESSAGE="$(git log -1 "$CIRCLE_SHA1" --pretty="%b")"

if [ "$AUTHOR_NAME" == "$COMMITTER_NAME" ]; then
  CREDITS="$AUTHOR_NAME authored & committed"
else
  CREDITS="$AUTHOR_NAME authored & $COMMITTER_NAME committed"
fi

TIMESTAMP=$(date --utc +%FT%TZ)
WEBHOOK_DATA='{
  "avatar_url": "https://www.saaves.com/storage/brochure/logo-circleci-icon1583764538.png",
  "embeds": [ {
    "author": {
      "name": "'"$3"' (Build #'"$CIRCLE_BUILD_NUM"')",
      "url": "'"$CIRCLE_BUILD_URL"'",
      "icon_url": "https://www.saaves.com/storage/brochure/logo-circleci-icon1583764538.png"
    },
    "title": "['"\`${CIRCLE_SHA1:0:7}\`"'] '"$COMMIT_SUBJECT"'",
    "url": "'"https://github.com/$CIRCLE_PROJECT_USERNAME/$CIRCLE_PROJECT_REPONAME/commit/$CIRCLE_SHA1"'",
    "description": "'"$CREDITS"'",
    "fields": [
      {
        "name": "Binary accuracy",
        "value": "'"$1"'",
        "inline": true
      }
    ],
    "timestamp": "'"$TIMESTAMP"'"
  } ]
}'

(curl --fail --progress-bar -A "TravisCI-Webhook" -H Content-Type:application/json -H X-Author:diasurgical -d "$WEBHOOK_DATA" "$2" \
  && echo -e "\\n[Webhook]: Successfully sent the webhook.") || echo -e "\\n[Webhook]: Unable to send webhook."
