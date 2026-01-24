package main

import (
	"fmt"
	"strings"

	"github.com/charmbracelet/bubbles/list"
	"github.com/charmbracelet/bubbles/textinput"
	tea "github.com/charmbracelet/bubbletea"
	"github.com/charmbracelet/lipgloss"
)

const (
	primary		= lipgloss.Color("#00ADAD")
	accent		= lipgloss.Color("#00FFFF")

	text		= lipgloss.Color("#F3F3F4")
	subtext		= lipgloss.Color("#5F5F5F")
	title 		= primary
	highlight 	= lipgloss.Color("#D65F86")

	light 		= lipgloss.Color("#F3F3F4")
	dark 		= subtext
	red			= lipgloss.Color("#D65F86")
	orange		= lipgloss.Color("#FF5F00")
	green		= lipgloss.Color("#D5F9DE")
	periwinkle	= lipgloss.Color("#677DB7")
)

// Pages/Container
var (
	mainContainerStyle = lipgloss.NewStyle()

	passwordPanelStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(accent)

	detailPanelStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(accent).
			Padding(0, 2)

	helpStyle = lipgloss.NewStyle().
			Foreground(dark).
			MarginTop(1)
)

// Components
var (
	titleStyle = lipgloss.NewStyle().
			Bold(true).
			Foreground(title)

	subtitleStyle = lipgloss.NewStyle().
			Foreground(accent).
			MarginBottom(1)

	normalStyle = lipgloss.NewStyle().
			Foreground(light)

	selectedStyle = lipgloss.NewStyle().
			Foreground(primary).
			Bold(true)

	boxStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			BorderForeground(accent)

	inputStyle = lipgloss.NewStyle().
			Border(lipgloss.NormalBorder()).
			Foreground(primary)
)

// Labels
var (
	usernameLabel = lipgloss.NewStyle().
		Foreground(accent).
		Render("Username:")

	passwordLabel = lipgloss.NewStyle().
		Foreground(accent).
		Render("Password:")

	urlLabel = lipgloss.NewStyle().
		Foreground(accent).
		Render("URL:")
)


// Help
var (
	key = lipgloss.NewStyle().Foreground(text)
	act = lipgloss.NewStyle().Foreground(subtext)
	sep = key.Render("\t")
)

const (
	// Layout ratios and margins
	splitRatio			= 0.3
	mainMargin			= 5
	listHeightOffset	= 10
	minListHeight		= 10
	
	// Container borders and padding
	listBorder 			= 4
	listPadding 		= 2
	detailBorder 		= 4
	detailPadding 		= 4
	mainContainerBorder = 4
	
	// Additional padding values
	listHeightPadding 	= 4
	listTotalOverhead	= 6  // listBorder + listPadding
	
	// Input field sizing
	defaultInputWidth	= 40
	maxInputWidth		= 60
	minInputWidth		= 30
	inputWidthOffset	= 40
	
	// Form sizing
	defaultFormWidth	= 60
	formWidthThreshold	= 80
	formWidthOffset		= 20
	
	// Detail view sizing
	defaultDetailWidth	= 60
	detailWidthThreshold= 80
	detailWidthOffset	= 20
	
	// Password masking
	maskedPasswordLength= 12
	
	// Text input limits
	serviceCharLimit	= 50
	usernameCharLimit	= 100
	passwordCharLimit	= 200
	urlCharLimit		= 200
	
	// Focus navigation
	maxFocusIndex		= 4
	numInputFields		= 4
	
	// List delegate
	listItemSpacing		= 1
)

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
		Foreground(text)
	
	// Style for selected item
	passwordList.Styles.SelectedTitle = passwordList.Styles.SelectedTitle.
		Foreground(highlight).
		BorderForeground(highlight)
	
	passwordList.Styles.SelectedDesc = passwordList.Styles.SelectedDesc. 
		Foreground(highlight).
		BorderForeground(highlight)

	passwordList.SetSpacing(listItemSpacing)
	
	l := list.New(entries, passwordList, 0, 0)
	l.Title = "Passwords"
	l.SetShowStatusBar(false)
	l.SetFilteringEnabled(false)
	l.SetShowHelp(false)

	// Initialize text inputs for add screen
	serviceInput := textinput.New()
	serviceInput.Placeholder = "e.g., GitHub, Gmail, etc."
	serviceInput.Focus()
	serviceInput.CharLimit = serviceCharLimit
	serviceInput.Width = defaultInputWidth

	usernameInput := textinput.New()
	usernameInput.Placeholder = "username or email"
	usernameInput.CharLimit = usernameCharLimit
	usernameInput.Width = defaultInputWidth

	passwordInput := textinput.New()
	passwordInput.Placeholder = "password"
	passwordInput.EchoMode = textinput.EchoPassword
	passwordInput.CharLimit = passwordCharLimit
	passwordInput.Width = defaultInputWidth

	urlInput := textinput.New()
	urlInput.Placeholder = "https://... (optional)"
	urlInput.CharLimit = urlCharLimit
	urlInput.Width = defaultInputWidth

	return model{
		currentScreen: mainScreen,
		list:          l,
		entries:       entries,
		serviceInput:  serviceInput,
		usernameInput: usernameInput,
		passwordInput: passwordInput,
		urlInput:      urlInput,
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
		usableWidth := msg.Width - mainMargin
		usableHeight := msg.Height - mainMargin
		
		// Split the width by splitRatio
		listWidth := int(float64(usableWidth) * splitRatio)
		
		// Size the list to take up most of the available space
		// Leave room for header, stats, and help text
		listHeight := usableHeight - listHeightOffset
		if listHeight < minListHeight {
			listHeight = minListHeight
		}
		
		m.list.SetSize(listWidth, listHeight)
		
		// Update input widths based on terminal size
		inputWidth := msg.Width - inputWidthOffset
		if inputWidth > maxInputWidth {
			inputWidth = maxInputWidth
		}
		if inputWidth < minInputWidth {
			inputWidth = minInputWidth
		}
		m.serviceInput.Width = inputWidth
		m.usernameInput.Width = inputWidth
		m.passwordInput.Width = inputWidth
		m.urlInput.Width = inputWidth
		
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
		if m.focusIndex > maxFocusIndex {
			m.focusIndex = 0
		} else if m.focusIndex < 0 {
			m.focusIndex = maxFocusIndex
		}

		cmds := make([]tea.Cmd, maxFocusIndex+1)
		for i := 0; i <= numInputFields-1; i++ {
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
		if m.focusIndex == maxFocusIndex { // Save button
			m.currentScreen = mainScreen
			m.focusIndex = 0
			// In real app, save the entry here
		}
		return m, nil
	}

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
		Foreground(text).
		Render(fmt.Sprintf("Total Passwords: %d | Last Updated: Today", len(m.entries)))

	help := helpStyle.Render(
		key.Render("a") + act.Render(" add password") + sep +
		key.Render("enter") + act.Render(" details") + sep +
		key.Render("q") + act.Render(" quit") + sep +
		key.Render("↑/↓") + act.Render(" navigate"),
	)

	// Calculate widths for split view
	usableWidth := m.width - mainMargin
	mainInnerWidth := usableWidth - mainContainerBorder
	
	// Calculate width based on sub-container overhead
	listOverhead 	:= listBorder + listPadding
	detailOverhead 	:= detailBorder + detailPadding
	contentWidth 	:= mainInnerWidth - (listOverhead + detailOverhead)
	
	// Split by splitRatio
	listContentWidth := int(float64(contentWidth) * splitRatio)
	detailContentWidth := contentWidth - listContentWidth
	
	// These are the TOTAL widths including borders and padding
	// Lipgloss.Width() sets the TOTAL width, not content width
	listTotalWidth := listContentWidth + listTotalOverhead
	detailTotalWidth := detailContentWidth + detailPadding * 2
	
	// Create the list with its own border
	listContent := passwordPanelStyle.
		Width(listTotalWidth).
		Height(m.list.Height() + listPadding * 2).
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
			Height(m.list.Height() + listPadding).
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
		lipgloss.WithWhitespaceForeground(dark),
	)
}

// Helper function to render the detail panel
func (m model) renderDetailPanel(entry passwordEntry, width int) string {
	var b strings.Builder
	
	// Entry name as title
	entryTitle := lipgloss.NewStyle().
		Foreground(red).
		Bold(true).
		Render(entry.name)
	b.WriteString(entryTitle + "\n\n")
	
	// Username
	b.WriteString(usernameLabel + "\n")
	b.WriteString(lipgloss.NewStyle().
		Foreground(text).
		Render(entry.username) + "\n\n")
	
	// Password (masked)
	b.WriteString(passwordLabel + "\n")
	
	// Create masked password
	maskedPassword := strings.Repeat("*", maskedPasswordLength)
	b.WriteString(lipgloss.NewStyle().
		Foreground(text).
		Render(maskedPassword) + "\n\n")
	
	// URL if exists
	if entry.url != "" {
		b.WriteString(urlLabel + "\n")
		b.WriteString(lipgloss.NewStyle().
			Foreground(green).
			Render(entry.url) + "\n")
	}
	
	// Render the panel with its own border
	return detailPanelStyle.
		Width(width).
		Height(m.list.Height() + listHeightPadding). // Match list height + padding
		Render(b.String())
}

func (m model) viewAdd() string {
	header := titleStyle.Render("Add New Password") + "\n"

	var b strings.Builder

	// Service
	serviceStyle := lipgloss.NewStyle().
		Foreground(accent).
		Render("Service Name:")
	b.WriteString(serviceStyle+ "\n")
	b.WriteString(m.serviceInput.View() + "\n\n")

	// Username
	b.WriteString(usernameLabel + "\n")
	b.WriteString(m.usernameInput.View() + "\n\n")

	
	// Password (masked)
	b.WriteString(passwordLabel + "\n")
	b.WriteString(m.passwordInput.View() + "\n\n")
	
	// URL if exists
	b.WriteString(urlLabel + "\n")
	b.WriteString(m.urlInput.View() + "\n")

	// Calculate proper width - use fixed width that works well
	formWidth := defaultFormWidth
	if m.width < formWidthThreshold {
		formWidth = m.width - formWidthOffset
	}

	form := boxStyle.
		Width(formWidth).
		Padding(1, 2).
		Render(b.String())

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
		lipgloss.WithWhitespaceForeground(dark),
	)
}

func (m model) viewEntry() string {
	if m.selectedEntry == nil {
		return "No entry selected"
	}

	e := m.selectedEntry
	header := titleStyle.Render(e.name) + "\n"

	var b strings.Builder

	b.WriteString(usernameLabel + "\n")
	b.WriteString(normalStyle.Render(e.username) + "\n\n")

	b.WriteString(passwordLabel + "\n")
	if m.showPassword {
		b.WriteString(normalStyle.Render(e.password) + "\n")
	} else {
		b.WriteString(normalStyle.Render("••••••••••••") + "\n")
	}
	b.WriteString("\n")

	if e.url != "" {
		b.WriteString(urlLabel + "\n")
		b.WriteString(normalStyle.Render(e.url) + "\n\n")
	}

	// Calculate proper width - use fixed width that works well
	detailWidth := defaultDetailWidth
	if m.width < detailWidthThreshold {
		detailWidth = m.width - detailWidthOffset
	}

	details := boxStyle.
		Width(detailWidth).
		Padding(1, 2).
		Render(b.String())

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
		lipgloss.WithWhitespaceForeground(dark),
	)
}

func main() {
	p := tea.NewProgram(initialModel(), tea.WithAltScreen())
	if _, err := p.Run(); err != nil {
		fmt.Printf("Error: %v", err)
	}
}
