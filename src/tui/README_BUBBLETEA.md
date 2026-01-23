# 🔒 Vault Password Manager TUI (Bubble Tea)

A beautiful Terminal User Interface for a password manager, built with Go and Bubble Tea - the same framework used by terminal.shop!

## Why Bubble Tea?

Terminal.shop uses **Bubble Tea** (Go) with **Lip Gloss** for styling. This gives you:
- The exact same aesthetic and feel as terminal.shop
- Fast, compiled Go binary
- Easy to integrate with C++ via stdin/stdout, gRPC, or shared libraries
- Professional, polished terminal UI

## Features

- ✨ Terminal.shop-inspired design with orange accents
- 🔍 Browse password entries with smooth navigation
- ➕ Add new password entries with beautiful forms
- 👁  View password details with show/hide toggle
- ⌨️  Full keyboard navigation
- 🎨 Styled with Lip Gloss (same as terminal.shop)

## Installation

### Prerequisites

1. Install Go (1.21 or later):
```bash
# macOS
brew install go

# Linux
wget https://go.dev/dl/go1.21.5.linux-amd64.tar.gz
sudo tar -C /usr/local -xzf go1.21.5.linux-amd64.tar.gz
export PATH=$PATH:/usr/local/go/bin

# Windows
# Download from https://go.dev/dl/
```

### Build and Run

```bash
# Clone or navigate to the project directory
cd vault

# Download dependencies
go mod tidy

# Build the binary
go build -o vault main.go

# Run it!
./vault
```

Or run directly without building:
```bash
go run main.go
```

## Keyboard Shortcuts

### Main Screen
- `↑/↓` or `j/k` - Navigate entries
- `Enter` - View selected entry
- `a` - Add new password
- `q` or `Ctrl+C` - Quit

### Add Password Screen
- `Tab` - Next field
- `Shift+Tab` or `↑` - Previous field
- `Enter` - Save (when on Save button)
- `Esc` - Cancel and go back

### View Password Screen
- `s` - Show/Hide password
- `Esc` or `q` - Go back to main screen

## Integration with C++

Since this is built in Go, you have several options to integrate with your C++ password manager:

### Option 1: Subprocess Communication (Easiest)
Run the TUI as a subprocess from C++ and communicate via stdin/stdout:

```cpp
// C++ side
#include <cstdio>
#include <iostream>

int main() {
    // Launch the Go TUI
    FILE* tui = popen("./vault", "r");
    
    // Read output, send commands
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), tui)) {
        std::cout << buffer;
    }
    
    pclose(tui);
    return 0;
}
```

### Option 2: CGO (Mixed Go/C++)
Use CGO to call C++ functions directly from Go:

```go
// vault.go
/*
#cgo LDFLAGS: -L. -lvault
#include "vault.h"
*/
import "C"

func getPasswords() []PasswordEntry {
    // Call your C++ library
    cPasswords := C.load_passwords()
    // Convert and return
}
```

### Option 3: gRPC (Best for Complex Apps)
Set up a gRPC server in C++ and have the Go TUI call it:

```protobuf
service PasswordVault {
    rpc ListPasswords(Empty) returns (PasswordList);
    rpc AddPassword(PasswordEntry) returns (Result);
    rpc GetPassword(PasswordID) returns (PasswordEntry);
}
```

### Option 4: Shared Database
Both C++ and Go read/write to the same encrypted database file (SQLite, etc.)

## Customization

All colors and styles are defined at the top of `main.go`. To match your brand:

```go
var (
    titleStyle = lipgloss.NewStyle().
        Bold(true).
        Foreground(lipgloss.Color("#FF6B00")).  // Change this color
        MarginLeft(2)
    
    // Modify other styles...
)
```

Common colors:
- Terminal.shop orange: `#FF6B00`
- GitHub dark: `#0D1117`
- VS Code blue: `#007ACC`

## Project Structure

```
vault/
├── main.go       # Main TUI application
├── go.mod        # Go dependencies
└── README.md     # This file
```

## Extending the TUI

To add features:

1. **Add new screens**: Create new screen constants and view functions
2. **Add functionality**: Implement in the `Update()` function
3. **Style it**: Use Lip Gloss styles at the top of the file
4. **Add components**: Import from `github.com/charmbracelet/bubbles`

## Bubble Tea Resources

- [Bubble Tea Docs](https://github.com/charmbracelet/bubbletea)
- [Bubbles Components](https://github.com/charmbracelet/bubbles)
- [Lip Gloss Styling](https://github.com/charmbracelet/lipgloss)
- [Terminal.shop Source](https://github.com/terminaldotshop/terminal) (TypeScript/Go)
- [Charm Examples](https://github.com/charmbracelet/bubbletea/tree/master/examples)

## Terminal.shop Similarity

This TUI mimics terminal.shop's aesthetic:
- Orange accent color (#FF6B00)
- Rounded borders
- Clean, minimal design
- Smooth keyboard navigation
- Professional typography

## Notes

- This is a UI demo - no actual encryption implemented
- Password entries are hardcoded for demonstration
- All buttons show actions but don't persist data
- Production use requires connecting to your C++ backend

## Next Steps for Production

1. Implement actual password storage (encrypted)
2. Add master password authentication
3. Connect to your C++ password vault backend
4. Add clipboard integration
5. Implement search/filter functionality
6. Add password generation
7. Add backup/restore features

## License

MIT

## Contributing

Pull requests welcome! This is meant to be a starting point for your own password manager TUI.
