#!/bin/bash
# Makes one commit per task (the assignment checks the commit history).
# Run ONCE inside the repository folder, AFTER you have added your screenshots:
#   git init && git branch -M main    (first time only)
#   bash commit_each_task.sh
git add README.md && git commit -m "Add README" -q
for n in 01 02 03 04 05 06 07 08 09 10 11 12; do
  git add Task$n && git commit -m "Task $n: code, input files and output screenshots" -q
done
git log --oneline
