# 数学考试系统 (MathExamSystem)

<div align="center">

![Version](https://img.shields.io/badge/版本-1.0-blue)
![Qt](https://img.shields.io/badge/Qt-6.2-green)
![C++](https://img.shields.io/badge/C++-17-orange)
![Platform](https://img.shields.io/badge/平台-跨平台-lightgrey)

**基于C++ Qt开发的现代化本地离线数学考试解决方案**

[项目简介](#项目简介) • [功能特性](#功能特性) • [技术架构](#技术架构) • [快速开始](#快速开始) • [使用指南](#使用指南)

</div>

## 项目简介

MathExamSystem 是一个专为**中小学数学教育**设计的本地离线桌面考试应用程序。系统采用现代化的Qt图形界面，支持完整的用户管理、智能题目生成、在线题库集成和自动评分功能，为教师和学生提供安全、高效的数学学习与评估平台。

---

## 功能特性

### 🎯 用户管理系统
- **安全注册流程**：邮箱验证 + 注册码机制
- **密码策略**：6-10位，必须包含大小写字母和数字
- **多角色支持**：小学、初中、高中三级学习阶段
- **数据加密**：本地加密存储，保障用户隐私

### 📚 智能题目系统
| 学段 | 题目类型 | 特色功能 |
|------|----------|----------|
| 小学 | 基础运算 | 加减乘除、括号运算 |
| 初中 | 代数运算 | 平方、开根号、简单方程 |
| 高中 | 高等数学 | 三角函数、复杂代数 |

### 🚀 核心功能
- **智能题库**：本地算法生成 
- **智能防重**：同一试卷内题目不重复
- **实时评分**：即时反馈，详细分析报告
- **进度跟踪**：答题进度可视化，时间管理

### 💾 数据管理
- **纯离线运行**：无需网络连接
- **本地持久化**：用户数据、考试记录安全存储
- **自动备份**：考试结果自动归档

---

## 技术架构

### 系统架构图
```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   前端界面层     │◄──►│   业务逻辑层      │◄──►│   数据访问层     │
│  (Qt Widgets)   │    │   (Services)     │    │   (Utils)       │
└─────────────────┘    └──────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   MainWindow    │    │   BackendCore    │    │   FileHelper    │
│ BackendInterface│    │   UserManager    │    │   StringHelper  │
│                 │    │ QuestionService  │    │                 │
│                 │    │   ExamManager    │    │                 │
│                 │    │ QuestionGenerator│    │                 │
└─────────────────┘    └──────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│  IPC通信桥接     │    │   核心业务逻辑    │    │   文件/字符串操作│
│  QLocalSocket   │    │   用户认证        │    │   数据持久化     │
│  JSON序列化      │    │   题目生成       │    │   工具函数      │
│  进程间通信      │    │   考试管理        │   │                 │
└─────────────────┘    └──────────────────┘    └─────────────────┘
```

### 核心技术栈
| 组件 | 技术选型         | 说明            |
|------|--------------|---------------|
| 开发框架 | C++ 17, Qt 5 | 现代化C++，跨平台GUI |
| 界面设计 | Qt Widgets   | 原生桌面应用体验      |
| 进程通信 | QLocalSocket | 前后端分离架构       |
| 数据存储 | 二进制文件 + JSON | 高效本地存储        |
| 网络通信 | libcurl      | 邮箱注册支持        |

### 核心类设计
```cpp
// 后端核心控制器
class BackendCore {
public:
    bool Login(const std::string& username, const std::string& password);
    bool GenerateExam(const std::string& userType, int questionCount);
    ExamResult SubmitExam();
};

// 题目生成抽象层
class QuestionGenerator {
public:
    virtual Question GenerateQuestion() = 0;
    virtual bool CheckDuplicate(const Question& question) = 0;
};
```

---

## 快速开始

### 环境要求
- **操作系统**：Windows 10/11, Linux
- **Qt版本**：Qt 5.14 或更高版本
- **编译器**：MSVC 2019+, MinGW 8.1+, 或 Clang
- **内存**：至少 2GB RAM

### 从源码构建
```bash
# 1. 克隆项目
git clone https://bdgit.educoder.net/hnu202326010127/jiedui.git

# 2. 打开Qt Creator
open MathExamSystem.pro

# 3. 配置构建套件
# 4. 构建项目 (Ctrl+B)
# 5. 运行程序 (Ctrl+R)
```

### 直接运行
已编译的可执行文件位于附件：
```
MathExamSystem/MathExamSystem.exe
```

---

## 使用指南

### 首次使用流程
1. **启动应用** → 运行 `MathExamSystem.exe`
2. **用户注册** → 输入邮箱获取注册码
3. **完善信息** → 设置密码，选择学习阶段
4. **开始考试** → 选择难度，生成试卷

### 考试流程详解
```
登录系统
    ↓
选择学习阶段 (小学/初中/高中)
    ↓
设置题目数量 (10-30题)
    ↓
开始答题 → 实时进度跟踪
    ↓
提交试卷 → 自动评分
    ↓
查看报告 → 详细分析
```

### 数据文件说明
| 文件 | 用途 | 位置 |
|------|------|------|
| `users.dat` | 用户账户数据 | 应用根目录 |
| `exam_data.dat` | 考试相关数据 | 应用根目录 |

---

## 项目结构

```
src/
├── backend/                          # 后端代码
│   ├── Core/
│   │   ├── BackendCore.cpp/h         # 后端核心控制器
│   ├── Services/                     # 业务服务层
│   │   ├── UserManager.cpp/h         # 用户管理服务
│   │   ├── QuestionService.cpp/h     # 题目服务
│   │   ├── ExamManager.cpp/h         # 考试管理
│   │   └── QuestionGenerator.cpp/h   # 题目生成器
│   ├── Models/                       # 数据模型
│   │   ├── UserInfo.h                # 用户信息模型
│   │   ├── Question.h                # 题目模型
│   │   └── ExamResult.h              # 考试结果模型
│   └── Utils/                        # 工具类
│       ├── FileHelper.cpp/h          # 文件操作
│       └── StringHelper.cpp/h        # 字符串处理
├── ipc/                             # 进程通信
│   ├── IPCServer.cpp/h              # IPC服务器
└── MathExamSystem/                  # 前端界面
    ├── main.cpp                     # 主程序入口
    ├── MainWindow.cpp/h/.ui         # 主窗口
    └── BackendInterface.cpp/h       # 前端接口
```

---

## 开发指南

### 架构设计原则
- **前后端分离**：GUI与业务逻辑完全解耦
- **模块化设计**：高内聚，低耦合
- **接口抽象**：易于扩展和维护
- **错误处理**：完善的异常处理机制

### 扩展开发
```cpp
// 添加新题型示例
class CustomQuestionGenerator : public QuestionGenerator {
public:
    Question GenerateQuestion() override {
        // 实现自定义题目生成逻辑
    }
    
    bool CheckDuplicate(const Question& question) override {
        // 实现查重逻辑
    }
};
```

### 代码规范
- 函数行数限制：≤ 40行（业务逻辑）
- 命名规范：驼峰命名法
- 注释要求：关键算法必须注释
- 错误处理：统一异常处理机制

---

## 故障排除

### 常见问题
| 问题 | 解决方案 |
|------|----------|
| 程序无法启动 | 检查Qt运行时库安装 |
| 连接后端失败 | 重启应用，检查防火墙设置 |
| 题目加载失败 | 验证网络连接，检查题库服务 |
| 数据文件损坏 | 删除损坏文件，系统自动重建 |

### 日志系统
- 实时运行日志：应用根目录下日志文件
- 调试模式：启用详细日志输出
- 错误追踪：完整的错误堆栈信息

---

## 版本管理

| 分支 | 说明 | 状态 |
|------|------|------|
| `main` | 稳定生产版本 | ✅ 推荐使用 |
| `develop` | 功能开发分支 | 🔧 新特性测试 |

---

## 许可证

本项目基于 **Qt开源许可证**，具体依赖库的许可证请参考相应文档。

---

<div align="center">

**🎯 提升数学技能，从智能考试开始**

*让数学学习变得更高效、更有趣！*

</div>
