# CBJQ_Mainland_VR_Start

最简方式启动国服尘白VR

项目地址：[https://github.com/LiuJiewenTT/CBJQ_Mainland_VR_Start](https://github.com/LiuJiewenTT/CBJQ_Mainland_VR_Start)<br>
项目主页：[https://LiuJiewenTT.github.io/CBJQ_Mainland_VR_Start](https://LiuJiewenTT.github.io/CBJQ_Mainland_VR_Start)<br>
下载页：[https://github.com/LiuJiewenTT/CBJQ_Mainland_VR_Start/releases](https://github.com/LiuJiewenTT/CBJQ_Mainland_VR_Start/releases)<br>

<div style="align-items: center; justify-content: center; display: flex; margin: 10px; gap: 10px">
   <img alt="GitHub Downloads (all assets, all releases)" src="https://img.shields.io/github/downloads/LiuJiewenTT/CBJQ_Mainland_VR_Start/total">
   <img alt="GitHub Release" src="https://img.shields.io/github/v/release/LiuJiewenTT/CBJQ_Mainland_VR_Start">
   <img alt="GitHub Actions Workflow Status" src="https://img.shields.io/github/actions/workflow/status/LiuJiewenTT/CBJQ_Mainland_VR_Start/jekyll-gh-pages.yml">
   <img alt="GitHub License" src="https://img.shields.io/github/license/LiuJiewenTT/CBJQ_Mainland_VR_Start">
</div>


## 使用

1. 你需要先下载[*UEVR*](https://github.com/praydog/UEVR/releases)。
2. 下载本项目的[*发行成品*](https://github.com/LiuJiewenTT/CBJQ_Mainland_VR_Start/releases)。
3. 将本项目的成品中，`CBJQ_Mainland_VR_Start.exe`（或可能存在的同目录其他文件）复制到你存放解压后的*UEVR*文件夹中。
4. 可选：右键将`CBJQ_Mainland_VR_Start.exe`发送到桌面快捷方式。
5. 运行`CBJQ_Mainland_VR_Start.exe`（或快捷方式）。
6. 启动游戏。

## 构建指南

本项目使用`GNU GCC 14.2.0`, `g++.exe`, `C++20`编译构建（`win32`, `seh`, `ucrt`, `x86_64`）。

构建程序须在项目根目录执行：`make -f src\Makefile`；<br>
程序会生成在`build/dest/`目录下。

> - 构建前你可能需要使用`prepare_dir`伪目标准备好所有所需目录。
> - `make`的来源请参考：[LiuJiewenTT/WinEnv4MinGW-GCC](https://github.com/LiuJiewenTT/WinEnv4MinGW-GCC)或[env-README.md](env-README.md)。
> - 项目模板的来源请参考：[LiuJiewenTT/WinGPPProjectStarter1](https://github.com/LiuJiewenTT/WinGPPProjectStarter1)或[starter-README.md](starter-README.md)。

