### Instalation and configuration Nvim
1. Install nvim (Ubuntu)
```
curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim-linux-x86_64.tar.gz
sudo rm -rf /opt/nvim
sudo tar -C /opt -xzf nvim-linux-x86_64.tar.gz
export PATH="$PATH:/opt/nvim-linux-x86_64/bin"
```
2. Install fonts `https://www.jetbrains.com/lp/mono/#how-to-install`
3. `git clone -b v2.0 https://github.com/NvChad/NvChad ~/.config/nvim --depth 1`
4. Install williamboaman/mason.nvim.
```
cd ~/.config/nvim/
nvim
ctrl+n
lua->custom->chadrc.lua
M.plugins = "cuson.plugins"

lua->custom->plugins.lua

```


### Usefull commands
```
space+th
ctrl+n - vim tree
ctlr+h - swith to left window
a - create new file
:TSInstall cpp typescript etc
m - mark file
c - copy file
p - paste file
r - rename file
spc + ff - find and open file
spc + fb - find in open files
spc + ch - cheetsheets
:vsp - vertical split
:sp - horizontal split
spc + x - close open file
:help lspconfig-all
:mksession mysession.vim
```

```
-- This file is for custom plugins
-- ~/.config/nvim/lua/custom/plugins.lua
local plugins = {
  {
    "neovim/nvim-lspconfig",
    config = function()
      require "plugins.configs.lspconfig"
      require "custom.configs.lspconfig"
    end,
  },
  {
    "williamboman/mason.nvim",
    opts = {
      ensure_installed = {
        "cpptools",
        "cpplint",
        "clangd",
        "clang-format",
        "codelldb",
        "cmakelang",
        "prettier",
        "mdx-analyzer",
        "dockerfile-language-server",
        "tailwindcss-language-server",
        "actionlint",
        "autotools-language-server",
        "chrome-debug-adapter",
        "copilot-language-server",
        "eslint_d",
        "eslint-lsp",
        "html-lsp",
        "htmlhint",
        "markmap-cli",
      }
    }
  }
}

-- lua/custom/configs/lspconfig.lua
local base = require("plugins.configs.lspconfig")
local on_attach = base.on_attach
local capabilities = base.capabilities

local lspconfig = require("lspconfig")

lspconfig.clangd.setup {
  on_attach = function(client, bufnr)
    client.server_capabilities.signatureHelpProvider = false
    on_attach(client, bufnr)
  end,
  capabilities = capabilities,
}
```