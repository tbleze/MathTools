@echo off
echo building replacements.txt ...
echo hf_==>REDACTED > replacements.txt

echo.
echo exec git filter-repo clean Hugging Face Token...

:: 检查是否已安装 git-filter-repo
where git-filter-repo >nul 2>nul
if errorlevel 1 (
    echo 未检测到 git-filter-repo，请先通过 pip 安装：
    echo     pip install git-filter-repo
    goto end
)

git filter-repo --replace-text replacements.txt

echo.
echo success

:end
pause
