# 获取 Conda 环境的路径
$CONDA_ENV_PATH = "D:/anaconda/envs/software"

# 设置 Python、Numpy、Matplotlib 相关的 include 目录
$PYTHON_INCLUDE = "$CONDA_ENV_PATH/include"
$NUMPY_INCLUDE = "$CONDA_ENV_PATH/Lib/site-packages/numpy/core/include"
$MATPLOTLIB_INCLUDE = "D:/MathTools/include"  # matplotlibcpp.h 目录

# 设置 Python 库目录
$PYTHON_LIB = "$CONDA_ENV_PATH"
$PYTHON_VERSION = "python38"  # Python 3.8 对应 python38

# 设置 PYTHONHOME 和 PYTHONPATH
$env:PYTHONHOME = "D:/anaconda/envs/software"
$env:PYTHONPATH = "D:/anaconda/envs/software/Lib;D:/anaconda/envs/software/Lib/site-packages"

# 确保 LIBRARY_PATH 包含 Python 相关库
$env:LIBRARY_PATH = "$PYTHON_LIB;" + $env:LIBRARY_PATH

# 获取所有 .cpp 文件（包括子目录）
$cppFiles = Get-ChildItem -Recurse -Filter "*.cpp" | ForEach-Object { $_.FullName }

# 组合编译命令
$compile_cmd = "g++ -std=c++11 -Wall -fPIC -o main.exe " + `
               "-I `"$PYTHON_INCLUDE`" " + `
               "-I `"$NUMPY_INCLUDE`" " + `
               "-I `"$MATPLOTLIB_INCLUDE`" " + `
               "-L `"$PYTHON_LIB`" -l$PYTHON_VERSION " + `
               ($cppFiles -join " ")

# 输出执行的编译命令
Write-Output "Compiling with: `n$compile_cmd"

# 运行编译命令
Invoke-Expression $compile_cmd

# 检查编译是否成功
if ($LASTEXITCODE -ne 0) {
    Write-Output "Compilation failed!"
    exit $LASTEXITCODE
}

Write-Output "Compilation successful! Run .\main.exe to execute."
