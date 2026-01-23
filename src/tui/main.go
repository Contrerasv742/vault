package main

import (
	"fmt"
	"strings"

	"github.com/charmbracelet/bubbles/key"
	"github.com/charmbracelet/bubbles/list"
	"github.com/charmbracelet/bubbles/textinput"
	tea "github.com/charmbracelet/bubbletea"
	"github.com/charmbracelet/lipgloss"
)

const (
	primary		= "#00ADAD"
	accent		= "#00FFFF"

	text		= "#F3F3F4"
	subtext		= "#5F5F5F"
	title 		= primary
	highlight 	= "#D65F86"

	light 		= "#F3F3F4"
	dark 		=  subtext
	red			= "#D65F86"
	orange		= "#FF5F00"
	green		= "#D5F9DE"
	perrywinkle	= "#677DB7"
)

var (
	titleStyle = lipgloss.NewStyle().
			Bold(true).
			Foreground(lipgloss.Color(title))

	subtitleStyle = lipgloss.NewStyle().
			Foreground(lipgloss.Color(accent)).
			MarginBottom(1)

	normalStyle = lipgloss.NewStyle().
			Foreground(lipgloss.Color(light))

	selectedStyle = lipgloss.NewStyle().
			Foreground(lipgloss.Color(primary)).
			Bold(true)

	helpStyle = lipgloss.NewStyle().
			Foreground(lipgloss.Color(dark)).
			MarginTop(1)

	boxStyle = lipgloss.NewStyle().
			Border(lipgloss.RoundedBorder()).
			BorderForeground(lipgloss.Color(accent))

	mainContainerStyle = lipgloss.NewStyle()

	passwordPanelStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(lipgloss.Color(accent))

	detailPanelStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(lipgloss.Color(accent))

	inputStyle = lipgloss.NewStyle().
			Border(lipgloss.RoundedBorder()).
			Foreground(lipgloss.Color(primary))

	buttonStyle = lipgloss.NewStyle().
			Background(lipgloss.Color(highlight)).
			Foreground(lipgloss.Color(dark)).
			Bold(true)

	buttonInactiveStyle = lipgloss.NewStyle().
				Border(lipgloss.RoundedBorder()).
				BorderForeground(lipgloss.Color(dark))
)

const split_ratio = 0.3

type screen int

const (
	mainScreen screen = iota
	addScreen
	viewScreen
)

type passwordEntry struct {
	name     string
	username string
	url      string
	password string
}

func (p passwordEntry) Title() string       { return p.name }
func (p passwordEntry) Description() string { return fmt.Sprintf("  %s", p.username) }
func (p passwordEntry) FilterValue() string { return p.name }

type model struct {
	currentScreen screen
	list          list.Model
	entries       []list.Item
	selectedEntry *passwordEntry
	currentIndex  int  // Track currently highlighted item in list
	
	// Add screen inputs
	serviceInput  textinput.Model
	usernameInput textinput.Model
	passwordInput textinput.Model
	urlInput      textinput.Model
	focusIndex    int
	
	// View screen state
	showPassword  bool
	
	width         int
	height        int
}

func initialModel() model {
	// Create sample password entries
	entries := []list.Item{
		passwordEntry{name: "GitHub", username: "user@example.com", url: "https://github.com", password: "secret123"},
		passwordEntry{name: "Gmail", username: "myemail@gmail.com", url: "https://gmail.com", password: "pass456"},
		passwordEntry{name: "AWS Console", username: "admin@company.com", url: "https://console.aws.amazon.com", password: "aws789"},
		passwordEntry{name: "Stripe", username: "billing@company.com", url: "https://stripe.com", password: "stripe000"},
		passwordEntry{name: "Database Server", username: "dbadmin", url: "", password: "db123456"},
		passwordEntry{name: "GitHub", username: "user@example.com", url: "https://github.com", password: "secret123"},
		passwordEntry{name: "GitHub", username: "user@example.com", url: "https://github.com", password: "secret123"},
		passwordEntry{name: "Gmail", username: "myemail@gmail.com", url: "https://gmail.com", password: "pass456"},
		passwordEntry{name: "AWS Console", username: "admin@company.com", url: "https://console.aws.amazon.com", password: "aws789"},
		passwordEntry{name: "Stripe", username: "billing@company.com", url: "https://stripe.com", password: "stripe000"},
		passwordEntry{name: "Database Server", username: "dbadmin", url: "", password: "db123456"},
		passwordEntry{name: "Gmail", username: "myemail@gmail.com", url: "https://gmail.com", password: "pass456"},
		passwordEntry{name: "AWS Console", username: "admin@company.com", url: "https://console.aws.amazon.com", password: "aws789"},
		passwordEntry{name: "Stripe", username: "billing@company.com", url: "https://stripe.com", password: "stripe000"},
		passwordEntry{name: "Database Server", username: "dbadmin", url: "", password: "db123456"},
	}

	// Set up list with custom passwordList
	passwordList := list.NewDefaultDelegate()
	
	// Style for normal (unselected) items
	passwordList.Styles.NormalTitle = passwordList.Styles.NormalTitle.
		Foreground(lipgloss.Color(text))
	
	// Style for selected item
	passwordList.Styles.SelectedTitle = passwordList.Styles.SelectedTitle.
		Foreground(lipgloss.Color(highlight)).
		BorderForeground(lipgloss.Color(highlight))
	
	passwordList.Styles.SelectedDesc = passwordList.Styles.SelectedDesc. 
		Foreground(lipgloss.Color(highlight)).
		BorderForeground(lipgloss.Color(highlight))

	passwordList.SetSpacing(1) // Space between items
	
	l := list.New(entries, passwordList, 0, 0)
	l.Title = "Passwords"
	l.SetShowStatusBar(false)
	l.SetFilteringEnabled(false)
	l.SetShowHelp(false)

	// Initialize text inputs for add screen
	si := textinput.New()
	si.Placeholder = "e.g., GitHub, Gmail, etc."
	si.Focus()
	si.CharLimit = 50
	si.Width = 40

	ui := textinput.New()
	ui.Placeholder = "username or email"
	ui.CharLimit = 100
	ui.Width = 40

	pi := textinput.New()
	pi.Placeholder = "password"
	pi.EchoMode = textinput.EchoPassword
	pi.CharLimit = 200
	pi.Width = 40

	urli := textinput.New()
	urli.Placeholder = "https://..."
	urli.CharLimit = 200
	urli.Width = 40

	return model{
		currentScreen: mainScreen,
		list:          l,
		entries:       entries,
		serviceInput:  si,
		usernameInput: ui,
		passwordInput: pi,
		urlInput:      urli,
		focusIndex:    0,
		showPassword:  false,
		currentIndex:  0,  // Initialize to first item
	}
}

func (m model) Init() tea.Cmd {
	return nil
}

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	switch msg := msg.(type) {
	case tea.WindowSizeMsg:
		m.width = msg.Width
		m.height = msg.Height
		
		// Calculate usable space with margins
		usableWidth := msg.Width - 5
		usableHeight := msg.Height - 5
		
		// Split the width: 60% for list, 40% for detail panel
		listWidth := int(float64(usableWidth) * split_ratio)
		
		// Size the list to take up most of the available space
		// Leave room for header, stats, and help text
		listHeight := usableHeight - 10
		if listHeight < 10 {
			listHeight = 10
		}
		
		m.list.SetSize(listWidth, listHeight)
		return m, nil

	case tea.KeyMsg:
		switch m.currentScreen {
		case mainScreen:
			return m.updateMain(msg)
		case addScreen:
			return m.updateAdd(msg)
		case viewScreen:
			return m.updateView(msg)
		}
	}

	return m, nil
}

func (m model) updateMain(msg tea.KeyMsg) (tea.Model, tea.Cmd) {
	switch msg.String() {
	case "q", "ctrl+c":
		return m, tea.Quit
	case "a":
		m.currentScreen = addScreen
		m.serviceInput.Focus()
		return m, textinput.Blink
	case "enter":
		if item, ok := m.list.SelectedItem().(passwordEntry); ok {
			m.selectedEntry = &item
			m.currentScreen = viewScreen
			m.showPassword = false
		}
		return m, nil
	}

	var cmd tea.Cmd
	m.list, cmd = m.list.Update(msg)
	
	// Update currentIndex to track which item is highlighted
	m.currentIndex = m.list.Index()
	
	return m, cmd
}

func (m model) updateAdd(msg tea.KeyMsg) (tea.Model, tea.Cmd) {
	switch msg.String() {
	case "esc", "ctrl+c":
		m.currentScreen = mainScreen
		m.focusIndex = 0
		return m, nil
	case "tab", "shift+tab", "up", "down":
		if msg.String() == "up" || msg.String() == "shift+tab" {
			m.focusIndex--
		} else {
			m.focusIndex++
		}
		if m.focusIndex > 4 {
			m.focusIndex = 0
		} else if m.focusIndex < 0 {
			m.focusIndex = 4
		}

		cmds := make([]tea.Cmd, 5)
		for i := 0; i <= 3; i++ {
			if i == m.focusIndex {
				switch i {
				case 0:
					cmds[i] = m.serviceInput.Focus()
				case 1:
					cmds[i] = m.usernameInput.Focus()
				case 2:
					cmds[i] = m.passwordInput.Focus()
				case 3:
					cmds[i] = m.urlInput.Focus()
				}
			} else {
				switch i {
				case 0:
					m.serviceInput.Blur()
				case 1:
					m.usernameInput.Blur()
				case 2:
					m.passwordInput.Blur()
				case 3:
					m.urlInput.Blur()
				}
			}
		}
		return m, tea.Batch(cmds...)
	case "enter":
		if m.focusIndex == 4 { // Save button
			m.currentScreen = mainScreen
			m.focusIndex = 0
			// In real app, save the entry here
		}
		return m, nil
	}

	// Update input widths based on terminal size
	inputWidth := m.width - 40
	if inputWidth > 60 {
		inputWidth = 60
	}
	if inputWidth < 30 {
		inputWidth = 30
	}
	m.serviceInput.Width = inputWidth
	m.usernameInput.Width = inputWidth
	m.passwordInput.Width = inputWidth
	m.urlInput.Width = inputWidth

	var cmd tea.Cmd
	switch m.focusIndex {
	case 0:
		m.serviceInput, cmd = m.serviceInput.Update(msg)
	case 1:
		m.usernameInput, cmd = m.usernameInput.Update(msg)
	case 2:
		m.passwordInput, cmd = m.passwordInput.Update(msg)
	case 3:
		m.urlInput, cmd = m.urlInput.Update(msg)
	}
	return m, cmd
}

func (m model) updateView(msg tea.KeyMsg) (tea.Model, tea.Cmd) {
	switch msg.String() {
	case "esc", "q", "ctrl+c":
		m.currentScreen = mainScreen
		return m, nil
	case "s":
		m.showPassword = !m.showPassword
		return m, nil
	}
	return m, nil
}

func (m model) View() string {
	switch m.currentScreen {
	case mainScreen:
		return m.viewMain()
	case addScreen:
		return m.viewAdd()
	case viewScreen:
		return m.viewEntry()
	}
	return ""
}

func (m model) viewMain() string {
	header := titleStyle.Render("VAULT") + "\n" +
		subtitleStyle.Render("Secure Password Manager")

	stats := lipgloss.NewStyle().
		Foreground(lipgloss.Color(text)).
		Render(fmt.Sprintf("Total Passwords: %d | Last Updated: Today", len(m.entries)))

	key := lipgloss.NewStyle().Foreground(lipgloss.Color(text))
	act := lipgloss.NewStyle().Foreground(lipgloss.Color(subtext))
	// sep := key.Render(" • ")
	sep := key.Render("\t")

	help := helpStyle.Render(
		key.Render("a") + act.Render(" add password") + sep +
		key.Render("enter") + act.Render(" fullscreen") + sep +
		key.Render("q") + act.Render(" quit") + sep +
		key.Render("↑/↓") + act.Render(" navigate"),
	)

	// Calculate widths for split view
	usableWidth := m.width - 5
	
	// Main container has border (2 chars per side = 4 total) and padding (0 from style)
	mainInnerWidth := usableWidth - 4
	
	// Each subcontainer overhead:
	// List: border(4) + padding left/right(1+1=2) = 6
	// Detail: border(4) + padding left/right(2+2=4) = 8
	// Total overhead: 6 + 8 = 14
	
	contentWidth := mainInnerWidth - 14
	
	// Split 60/40
	listContentWidth := int(float64(contentWidth) * split_ratio)
	detailContentWidth := contentWidth - listContentWidth
	
	// These are the TOTAL widths including borders and padding
	// Lipgloss .Width() sets the TOTAL width, not content width
	listTotalWidth := listContentWidth + 6
	detailTotalWidth := detailContentWidth + 8
	
	// Create the list with its own border
	listContent := passwordPanelStyle.
		Width(listTotalWidth).
		Height(m.list.Height() + 4). // Add height for border + padding
		Render(m.list.View())
	
	// Create the detail panel on the right
	var detailPanel string
	if m.currentIndex >= 0 && m.currentIndex < len(m.entries) {
		if entry, ok := m.entries[m.currentIndex].(passwordEntry); ok {
			detailPanel = m.renderDetailPanel(entry, detailTotalWidth)
		}
	} else {
		// Empty detail panel if no selection
		detailPanel = detailPanelStyle.
			Width(detailTotalWidth).
			Height(m.list.Height() + 4). // Match list height
			Align(lipgloss.Center, lipgloss.Center).
			Render("Select a password\nto view details")
	}
	
	// Combine list and detail panel horizontally
	splitView := lipgloss.JoinHorizontal(
		lipgloss.Top,
		listContent,
		detailPanel,
	)
	
	// Wrap everything in the main container
	mainContainer := mainContainerStyle.
		Width(usableWidth).
		Render(splitView)
	
	content := lipgloss.JoinVertical(
		lipgloss.Center,
		header,
		stats,
		mainContainer,
		help,
	)

	// Center the content vertically and horizontally
	return lipgloss.Place(
		m.width,
		m.height,
		lipgloss.Center,
		lipgloss.Center,
		content,
		lipgloss.WithWhitespaceChars(" "),
		lipgloss.WithWhitespaceForeground(lipgloss.Color(dark)),
	)
}

// Helper function to render the detail panel
func (m model) renderDetailPanel(entry passwordEntry, width int) string {
	var b strings.Builder
	
	// Entry name as title
	entryTitle := lipgloss.NewStyle().
		Foreground(lipgloss.Color(red)).
		Bold(true).
		Render(entry.name)
	b.WriteString(entryTitle + "\n\n")
	
	// Username
	labelStyle := lipgloss.NewStyle().
		Foreground(lipgloss.Color(accent)).
		Render("Username:")
	b.WriteString(labelStyle + "\n")
	b.WriteString(lipgloss.NewStyle().
		Foreground(lipgloss.Color(text)).
		Render(entry.username) + "\n\n")
	
	// Password (masked)
	passwordLabel := lipgloss.NewStyle().
		Foreground(lipgloss.Color(accent)).
		Render("Password:")
	b.WriteString(passwordLabel + "\n")
	
	// Create masked password
	maskedPassword := strings.Repeat("*", 12)
	b.WriteString(lipgloss.NewStyle().
		Foreground(lipgloss.Color(text)).
		Render(maskedPassword) + "\n\n")
	
	// URL if exists
	if entry.url != "" {
		urlLabel := lipgloss.NewStyle().
			Foreground(lipgloss.Color(accent)).
			Render("URL:")
		b.WriteString(urlLabel + "\n")
		b.WriteString(lipgloss.NewStyle().
			Foreground(lipgloss.Color(green)).
			Render(entry.url) + "\n")
	}
	
	// Render the panel with its own border
	return detailPanelStyle.
		Width(width).
		Height(m.list.Height() + 4). // Match list height + padding
		Render(b.String())
}

func (m model) viewAdd() string {
	header := titleStyle.Render("Add New Password") + "\n"

	var b strings.Builder

	b.WriteString(normalStyle.Render("Service Name:") + "\n")
	b.WriteString(inputStyle.Render(m.serviceInput.View()) + "\n\n")

	b.WriteString(normalStyle.Render("Username/Email:") + "\n")
	b.WriteString(inputStyle.Render(m.usernameInput.View()) + "\n\n")

	b.WriteString(normalStyle.Render("Password:") + "\n")
	b.WriteString(inputStyle.Render(m.passwordInput.View()) + "\n\n")

	b.WriteString(normalStyle.Render("URL (optional):") + "\n")
	b.WriteString(inputStyle.Render(m.urlInput.View()) + "\n\n")

	form := boxStyle.Width(m.width/2).Render(b.String())

	key := lipgloss.NewStyle().Foreground(lipgloss.Color(text))
	act := lipgloss.NewStyle().Foreground(lipgloss.Color(subtext))
	sep := key.Render("\t")

	help := helpStyle.Render(
		key.Render("tab") + act.Render(" next/field") + sep +
		key.Render("enter") + act.Render(" save") + sep +
		key.Render("esc") + act.Render(" cancel") + sep +
		key.Render("↑/↓") + act.Render(" navigate"),
	)

	content := lipgloss.JoinVertical(
		lipgloss.Center,
		header,
		form,
		help,
	)

	// Center the content vertically and horizontally
	return lipgloss.Place(
		m.width,
		m.height,
		lipgloss.Center,
		lipgloss.Center,
		content,
		lipgloss.WithWhitespaceChars(" "),
		lipgloss.WithWhitespaceForeground(lipgloss.Color(dark)),
	)
}

func (m model) viewEntry() string {
	if m.selectedEntry == nil {
		return "No entry selected"
	}

	e := m.selectedEntry
	header := titleStyle.Render(e.name) + "\n"

	var b strings.Builder

	b.WriteString(lipgloss.NewStyle().Foreground(lipgloss.Color(primary)).Render("Username/Email:") + "\n")
	b.WriteString(normalStyle.Render(e.username) + "\n\n")

	b.WriteString(lipgloss.NewStyle().Foreground(lipgloss.Color(primary)).Render("Password:") + "\n")
	if m.showPassword {
		b.WriteString(normalStyle.Render(e.password) + "\n")
	} else {
		b.WriteString(normalStyle.Render("••••••••••••") + "\n")
	}
	b.WriteString("\n")

	if e.url != "" {
		b.WriteString(lipgloss.NewStyle().Foreground(lipgloss.Color(primary)).Render("URL:") + "\n")
		b.WriteString(normalStyle.Render(e.url) + "\n\n")
	}

	details := boxStyle.Width(m.width/3).Render(b.String())


	key := lipgloss.NewStyle().Foreground(lipgloss.Color(text))
	act := lipgloss.NewStyle().Foreground(lipgloss.Color(subtext))
	sep := key.Render("\t")

	help := helpStyle.Render(
		key.Render("s") + act.Render(" show/hide") + sep +
		key.Render("e") + act.Render(" edit") + sep +
		key.Render("esc") + act.Render(" back"),
	)

	content := lipgloss.JoinVertical(
		lipgloss.Center,
		header,
		details,
		help,
	)

	// Center the content vertically and horizontally
	return lipgloss.Place(
		m.width,
		m.height,
		lipgloss.Center,
		lipgloss.Center,
		content,
		lipgloss.WithWhitespaceChars(" "),
		lipgloss.WithWhitespaceForeground(lipgloss.Color(dark)),
	)
}

type keyMap struct {
	Up    key.Binding
	Down  key.Binding
	Enter key.Binding
	Quit  key.Binding
}

func main() {
	p := tea.NewProgram(initialModel(), tea.WithAltScreen())
	if _, err := p.Run(); err != nil {
		fmt.Printf("Error: %v", err)
	}
}

