#!/usr/bin/fish
git archive --format=tar HEAD --output=../(basename (pwd)).tar
