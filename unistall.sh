#!/bin/bash
set -e

APP_NAME="vextra"
GLOBAL_PATH="/usr/local/bin/$APP_NAME"
LOCAL_PATH="$HOME/.local/bin/$APP_NAME"

echo "🧹 Uninstalling $APP_NAME..."

# 1️⃣ Try removing global install
if [ -f "$GLOBAL_PATH" ]; then
    echo "📂 Found global installation at $GLOBAL_PATH"
    sudo rm -f "$GLOBAL_PATH"
    echo "✅ Removed global installation."
fi

# 2️⃣ Try removing local install
if [ -f "$LOCAL_PATH" ]; then
    echo "📂 Found local installation at $LOCAL_PATH"
    rm -f "$LOCAL_PATH"
    echo "✅ Removed local installation."
fi

# 3️⃣ Check result
if [ ! -f "$GLOBAL_PATH" ] && [ ! -f "$LOCAL_PATH" ]; then
    echo "✅ $APP_NAME fully uninstalled."
else
    echo "⚠️ Could not remove one or more installations. Try running with sudo."
fi

echo ""
echo "🧭 Uninstall complete!"
