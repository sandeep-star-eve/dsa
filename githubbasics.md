# Complete Guide to Using GitHub for Code Sync

## Step 1: Create a GitHub Account

1. Go to [github.com](https://github.com)
2. Click **Sign up**
3. Enter email, password, username
4. Verify your email

---

## Step 2: Install Git on Your Computers

**Windows (if not installed):**
```powershell
winget install Git.Git
```

Or download from [git-scm.com](https://git-scm.com)

---

## Step 3: Create a New Repository

1. Log in to GitHub → Click **+** → **New repository**
2. Name it: `dsa` (or any name)
3. Set to **Public** or **Private**
4. Click **Create repository**
5. Copy the URL (e.g., `https://github.com/yourusername/dsa.git`)

---

## Step 4: Push Your Code from Laptop
git add .
git commit -m "Add stackop.c"
git push

Open terminal in your `c:\dsa` folder:

```powershell
# Initialize git (if not already)
git init

# Add all files
git add .

# Commit with a message
git commit -m "Initial commit"

# Connect to GitHub (use your repo URL)
git remote add origin https://github.com/yourusername/dsa.git

# Push to GitHub
git push -u origin main
```

---

## Step 5: Clone on Lab Computer

```powershell
# Navigate to where you want the code
cd c:\

# Clone the repository
git clone https://github.com/yourusername/dsa.git
```

---

## Step 6: Syncing Changes

**After making changes on laptop:**
```powershell
git add .
git commit -m "Describe your changes"
git push
```

**On lab computer, before working:**
```powershell
git pull
```

---

## Step 7: Access on Mobile

### Option A: GitHub Mobile App
1. Download **GitHub** app from App Store/Play Store
2. Sign in with your GitHub account
3. Browse your repos, view code, create/edit files

### Option B: GitHub Web
1. Open `github.com` in mobile browser
2. Sign in → Browse your `dsa` repo
3. View files, create branches, even edit code

### Option C: VS Code for Web (github.dev)
1. Go to `github.com/yourusername/dsa`
2. Press `.` (dot key) → Opens in-browser VS Code
3. Edit files directly in browser

---

## Quick Reference Summary

| Action | Command |
|--------|---------|
| First push | `git add . && git commit -m "msg" && git push -u origin main` |
| Update code | `git add . && git commit -m "msg" && git push` |
| Get latest | `git pull` |
| Check status | `git status` |