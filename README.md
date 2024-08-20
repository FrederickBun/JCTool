<div align="center">
    	<strong><span style="font-size:32px;">Just Command Tool</span></strong>&emsp;
	<img src=".\icon\server.ico" width="26" height="26"/>
</div>
<div align="center">
    <img src="https://raster.shields.io/badge/Author-A6n6d6y6_llzzmm645-red"/>&ensp;
    <img src="https://raster.shields.io/badge/Compatible_OS-Windows-blue"/>&ensp;
    <img src="https://raster.shields.io/badge/Top_language-C++-green"/>&ensp;
</div>

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>简介</strong></h2>

一个简单的命令行，支持连接**局域网**客户端进行命令操作。

使用 `windows` 下默认的套接字及多线程库、[lzmsocket.h](https://github.com/llzzmm645/lzmsocket)、以及自己封装的 `andycolor.h`。

支持传输文件、执行命令，自定义空间较大。

配色风格仿 `cmder`，自带透明度。

![css.png](https://img.picui.cn/free/2024/07/21/669cced547f60.png)

<p align="center">server.exe 样式</p>

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>目的</strong></h2>

快速传输文件、执行操作。

~~肯定不是用来JC别人的。~~

**声明**：本工具应用于正当用途，如有出现损坏他人权益的行为，本工具一概不负责任！

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>功能</strong></h2>

连接客户端、执行命令、拉取/上传文件、更改设置、扩展命令行。

值得注意的是，客户端没有窗口界面，所以这是一个单向传输。

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>安装指南</strong></h2>

下载压缩包解压到目录后，确保已经配置好 `g++` 环境变量，运行 `build.bat`。

在 `.\bin`  文件夹中会有 `server.exe` 与 `client.exe`，可以直接开始使用了（`client` 只适用于你的 `server`）。

**注意**：环境为 `windows` 下，版本不得低于  `isoc++11/gnuc++11`。

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>使用说明</strong></h2>

### 开始

在他人电脑上打开 `client.exe` 后，`client.exe` 会寻找空闲的 `server.exe` 5分钟（10秒尝试一次），超时则退出。

最后在`server.exe` 中键入命令，就可以开始愉快的使用了。

***

### 命令行选项

#### 概述

由于技术实现及防止歧义问题：

- 所有本应一起识别的字符串中含空格的，一律使用双引号 `"` 以标记，在双引号中用 `\"` 以转义。
- 所有本应一起识别的字符串中不含空格的，允许不使用双引号 `"` 以标记，允许不用 `\"`  以转义，可以直接 使用 `"`。

约定默认起始路径在双方用户文件夹下。

***

#### 预设置

因为作者太菜不会写 `*.json`，`*.ini` 也有些像~~就是~~C++头文件该后缀名。所以部分预设值写的很乱，请见谅。

在 `.\setting` 中：

- ip.ini 你在局域网中的IP地址，在编译时会自动帮你获取；
- port.ini 连接的端口，默认为 `1145`；
- precmd  程序预先执行的命令，比如 `chcp 65001` 等等。

***

#### 路径回显

显示格式为：

<pre>
	localhost[在你电脑上的路径] <=> 客户端IP地址[在客户端电脑上的路径]
	$ ......
</pre>
***

#### 并行命令

在 `JCTool` 中，使用 `; & |` 作为并行符，以将两行命令合并为一行（仿 `Linux`）

- `;` 代表两行命令没有联系，无论何种情况，应顺序执行两行代码；
- `&` 代表如果前面的命令执行**成功**，则执行后面的代码；
- `|` 代表如果前面的命令执行**失败**，则执行后面的代码。

注意：以上三种并行符**没有**优先级顺序，从左至右依次结合。

特殊的，你应该使用空格以分割并行符与语句，形如 `cmd1 opt cmd2`。

***

#### 命令解释

**cmdl/cmdv/cmdd(cmd)**：

- `cmdl` 在自己的路径下执行命令；
- `cmdv` 在客户端的路径下执行命令，不启用监听返回值功能；
- `cmdd(cmd)` 在客户端的路径下执行命令，启用监听返回值功能（在客户端结束进程前，不会结束监听）。

使用方法形如 `cmdl/cmdv/cmdd opt`，其中 `opt` 是执行的命令。

**push/pull**：

- `push` 服务端向客户端推送文件；

- `pull` 服务端向客户端拉取文件。

使用方法形如 `push/pull file1 file2`，其中 `file1` 是源文件全路径，`file2` 是新文件全路径。

**cdl/cdc(cd)**：

- `cdl` 更改服务端路径；

- `cdc(cd)` 更改客户端路径。

使用方法形如 `cdl/cdc path`，其中 `path` 是目录路径。

**msg**：

向客户端发送信息

使用方法形如 `msg txt title icon`。

其中 `txt` 是消息内容，`title`是消息标题，`icon` 是图标，对应意义如下面表格：

<div class="table-responsive">
	<table class="table table-hover">
		<thead align="center">
			<tr>
				<th><code>icon</code> 选项</th>
                <th>意义</th>
                <th>图标</th>
			</tr>
		</thead>
		<tbody align="center">
			<tr>
				<td><code>!</code></td>
				<td>警告</td>
                <td><img src="https://img.picui.cn/free/2024/07/21/669c74801fac8.png"/></td>
			</tr>
            <tr>
				<td><code>?</code></td>
				<td>询问</td>
                <td><img src="https://img.picui.cn/free/2024/07/21/669c748006031.png"/></td>
			</tr>
            <tr>
				<td><code>i</code></td>
				<td>提示/信息</td>
                <td><img src="https://img.picui.cn/free/2024/07/21/669c748003fda.png"/></td>
			</tr>
            <tr>
				<td><code>x</code></td>
				<td>错误</td>
                <td><img src="https://img.picui.cn/free/2024/07/21/669c748022efb.png"/></td>
			</tr>
            <tr>
                <td>其他非空字符</td>
                <td>无</td>
                <td></td>
            </tr>
		</tbody>
	</table>
</div>
***

**stty**：

设置一些选项的值。

- 对于值为布尔型的选项，参数为 `stty [+/-]item`。其中 `item` 是选项名称，`+/-` 是设置为 `true/false`；
- 对于值为整数型的选项，参数为 `stty Iitem=val`。其中 `item` 是选项名称，`val` 是值（$val\in[-2^{31}\sim2^{31}-1]$）；
- 对于值为实数型的选项，参数为 `stty Ritem=val`。其中 `item` 是选项名称，`val` 是值（$val\in[-1.79\times10^{308}\sim1.79\times10^{308}],\epsilon\ge10^{-15}$）；
- 对于值为字符串的选项，参数为 `stty Sitem=val`。其中 `item` 是选项名称，`val` 是值（$|val|\in[1,10^3]$）。

目前有意义的选项有：

<div class="table-responsive">
	<table class="table table-hover">
		<thead align="center">
			<tr>
				<th>类型::名称</th>
                <th>意义</th>
                <th>取值范围</th>
                <th>默认值</th>
			</tr>
		</thead>
		<tbody align="center">
			<tr>
				<td>bool::echo_input</td>
				<td>是否回显输入</td>
                <td>true/false</td>
                <td>true</td>
			</tr>
            <tr>
				<td>bool::echo_input</td>
				<td>是否回显路径</td>
                <td>true/false</td>
                <td>true</td>
			</tr>
            <tr>
				<td>int::window_alpha</td>
				<td>窗口透明度</td>
                <td>0~255</td>
                <td>192</td>
			</tr>
		</tbody>
	</table>
</div>
**exit**：退出。

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>常见错误及原因</strong></h2>

<div class="table-responsive">
	<table class="table table-hover">
		<thead align="center">
			<tr>
				<th>名称</th>
                <th>意义</th>
                <th>常见原因</th>
			</tr>
		</thead>
		<tbody align="center">
			<tr>
				<td>Failed to init server.</td>
                <td>初始化服务端错误</td>
                <td>端口被占用</td>
			</tr>
            <tr>
				<td>Cannot find the file.</td>
                <td>无法寻找到文件</td>
                <td>文件不存在</td>
			</tr>
            <tr>
				<td>Cannot open the file.</td>
                <td>无法打开到文件</td>
                <td>路径不存在/无权限写入</td>
			</tr>
            <tr>
				<td>Cannot find the path.</td>
                <td>无法寻找到路径</td>
                <td>路径不存在</td>
			</tr>
            <tr>
				<td>Unknown setting item.</td>
                <td>未知设置选项</td>
                <td>选项错误</td>
			</tr>
            <tr>
				<td>Unknown setting type.</td>
                <td>未知设置类型</td>
                <td>类型错误</td>
			</tr>
            <tr>
				<td>Unknown Command.</td>
                <td>未知命令</td>
                <td>命令错误</td>
			</tr>
		</tbody>
	</table>
</div>

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>示例</strong></h2>

![server.png](https://img.picui.cn/free/2024/07/19/6699d9eca3457.png)

<p align="center">服务端 server.exe 界面</p>

![client.png](https://img.picui.cn/free/2024/07/19/6699d9ebb7492.png)

<p align="center">客户端 cmd 查看界面与消息界面</p>

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>贡献指南</strong></h2>

首先非常感谢大家选择和使用 `JCTool`！

我们鼓励任何形式的参与社区贡献：

- 将遇到的问题通过 `github` 上 `issue` 的形式反馈出来
- 回答别人遇到的 `issue` 问题
- 帮助完善文档
- 帮助项目增加测试用例
- 为代码添加注释
- 提交修复 Bug 或者 Feature 的 PR

<h2 style="border-left:6px solid #2196F3;background:#ddffff;padding:14px;letter-spacing:1px;"><strong>维护者</strong></h2>
