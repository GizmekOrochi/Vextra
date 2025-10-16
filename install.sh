#!/bin/bash
set -e

APP_NAME="vextra"
BUILD_DIR="src"
BIN_PATH="bin/$APP_NAME"
INSTALL_PATH="/usr/local/bin/$APP_NAME"

echo "⚙️  Installing $APP_NAME..."

# 1️⃣ Build the program
if [ ! -f "$BIN_PATH" ]; then
    echo "🛠️  Building $APP_NAME..."
    (cd "$BUILD_DIR" && make com)
else
    echo "✅ Found prebuilt binary."
fi

# 2️⃣ Verify binary exists
if [ ! -f "$BIN_PATH" ]; then
    echo "❌ Build failed: binary not found at $BIN_PATH"
    exit 1
fi

# 3️⃣ Try installing to /usr/local/bin (requires sudo)
echo "📂 Installing binary to $INSTALL_PATH..."
if sudo cp -f "$BIN_PATH" "$INSTALL_PATH"; then
    sudo chmod +x "$INSTALL_PATH"
    echo "✅ $APP_NAME installed globally at $INSTALL_PATH"
else
    echo "⚠️ Could not install to /usr/local/bin. Installing locally..."
    LOCAL_BIN="$HOME/.local/bin"
    mkdir -p "$LOCAL_BIN"
    cp -f "$BIN_PATH" "$LOCAL_BIN/"
    chmod +x "$LOCAL_BIN/$APP_NAME"
    echo "✅ Installed to $LOCAL_BIN/$APP_NAME"
    echo "💡 Add this to your PATH if needed:"
    echo "   export PATH=\"\$PATH:$LOCAL_BIN\""
fi

echo ""
echo "🚀 You can now run: $APP_NAME"
