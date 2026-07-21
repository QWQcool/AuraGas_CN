# AuraGas

Gameplay Ability System (GAS) 学习项目 | UE 5.8 | C++ & Blueprint

## 新机快速启动

### 前置要求

| 依赖 | 版本 | 备注 |
|---|---|---|
| Unreal Engine | 5.8 | Epic Launcher 安装 |
| Node.js | 18+ | MCP 工具链需要 |
| Git LFS | 任意 | 大文件支持 |

### 1. 编译项目

```powershell
# 克隆仓库
git clone <repo-url> AuraGas
cd AuraGas

# 双击打开项目（首次需编译 C++ + UE_MCP_Bridge 插件）
# 或右键 .uproject → Switch Unreal Engine Version → 5.8
start AuraGas.uproject
```

首次打开时 UE 会自动编译：
- `Source/AuraGas/` — 游戏 C++ 代码
- `Plugins/UE_MCP_Bridge/` — MCP 桥接插件

编译完成后会弹出 "GameFeatureData" 提示，点 **Yes** 添加条目即可。

### 2. 启用 MCP 工具链

UE-MCP 让 AI 助手直接读写蓝图变量、函数、事件图和 UMG 控件树。

**步骤 A：启用 IDE 插件**

`Edit → Plugins` → 搜索启用以下插件：

| 插件 | 用途 |
|---|---|
| `Unreal MCP` | Anthropic MCP 服务器 |
| `MCP Client Toolset` | MCP 工具注册适配器 |
| `All Toolsets` | 聚合所有工具集 |
| `UE_MCP_Bridge` | ✅ 已随项目编译 |

**步骤 B：启用 MCP 服务器自启动**

`Edit → Editor Preferences → General → Model Context Protocol`：
- 勾选 `Auto Start Server`
- 默认端口 `8000`，路径 `/mcp`

**步骤 C：配置 CodeBuddy**

将以下条目添加到 `C:/Users/<用户名>/.codebuddy/mcp.json` 的 `mcpServers` 中：

```json
{
  "ue-mcp": {
    "command": "npx",
    "args": ["ue-mcp", "<项目路径>/AuraGas.uproject"],
    "timeout": 60000
  }
}
```

> 首次运行 `npx ue-mcp` 会自动安装 npm 包，之后每次 CodeBuddy 启动会自动连接编辑器。

### 3. 验证

1. 打开 AuraGas.uproject
2. 重启 CodeBuddy
3. AI 可调用 `blueprint.read`、`widget.read_tree` 等 111 个工具

### MCP 配置通用解

MCP 客户端配置采用**同一 JSON 结构**，仅配置路径不同。核心参数：

```json
{
  "command": "npx",
  "args": ["ue-mcp", "<项目绝对路径>/AuraGas.uproject"]
}
```

| AI 客户端 | 配置文件路径 | 格式 |
|---|---|---|
| **Claude Desktop** | `%APPDATA%\Claude\claude_desktop_config.json` | JSON |
| **Cursor** | `.cursor/mcp.json`（项目根目录） | JSON |
| **Codex** | `~/.codex/config.toml` | TOML |
| **CodeBuddy** | `~/.codebuddy/mcp.json` | JSON |
| **VS Code** | 安装 MCP 扩展后在设置中配置 | UI / JSON |
| **Rider** | 安装 MCP 扩展后在 `Settings → MCP` 配置 | UI / JSON |

#### Claude Desktop

```json
{
  "mcpServers": {
    "ue-mcp": {
      "command": "npx",
      "args": ["ue-mcp", "C:/UE/AuraGas/AuraGas.uproject"]
    }
  }
}
```

#### Cursor

```json
{
  "mcpServers": {
    "ue-mcp": {
      "command": "npx",
      "args": ["ue-mcp", "C:/UE/AuraGas/AuraGas.uproject"]
    }
  }
}
```

#### Codex (`~/.codex/config.toml`)

```toml
[mcp_servers.ue-mcp]
command = "npx"
args = ["ue-mcp", "C:/UE/AuraGas/AuraGas.uproject"]
enabled = true
```

#### CodeBuddy (`~/.codebuddy/mcp.json`)

```json
{
  "mcpServers": {
    "ue-mcp": {
      "command": "npx",
      "args": ["ue-mcp", "C:/UE/AuraGas/AuraGas.uproject"],
      "timeout": 60000
    }
  }
}
```

#### VS Code / Rider

在 IDE 中搜索并安装 MCP 扩展，然后添加服务器：
- **Command**: `npx`
- **Arguments**: `ue-mcp C:/UE/AuraGas/AuraGas.uproject`

> **首次运行** `npx ue-mcp` 会自动安装 npm 包。之后每次 IDE 启动自动连接编辑器。
> 路径必须使用**正斜杠** `/`，不支持反斜杠 `\`。

### MCP 核心工具速览

| 工具 | 读/写 | 用例 |
|---|---|---|
| `blueprint.read` | 读 | 组件树、继承链 |
| `blueprint.read_graph` | 读 | 事件图节点+引脚+连线 |
| `blueprint.list_variables` | 读 | 变量名+类型+默认值 |
| `blueprint.list_functions` | 读 | 函数签名+参数 |
| `widget.read_tree` | 读 | UMG 控件层级结构 |
| `widget.get_properties` | 读 | 控件属性含子控件递归 |
| `gas.*` | 读写 | GAS 属性/效果/技能 |
| `blueprint.create` 等 | 写 | 创建/编辑/编译蓝图 |

### 项目文档

| 文档 | 内容 |
|---|---|
| [系统架构分析.md](系统架构分析.md) | 类继承、蓝图详情、UI 控件树、MVC 数据流 |
| [学习记录.md](学习记录.md) | 开发时间线、git 提交记录、MCP 探索历程 |

### `.gitignore`

已排除的生成文件：`.vscode` `.vs` `.vsconfig` `.idea/` `*.sln` `*.slnx` `Binaries/` `Intermediate/` `Saved/` `DerivedDataCache/`

---

*Last updated: 2026-07-21 | Engine: UE 5.8*
