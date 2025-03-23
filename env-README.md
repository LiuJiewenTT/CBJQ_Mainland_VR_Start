# WinEnv4MinGW-GCC

This is a Windows environment initiator for MinGW-GCC.

Currently, the most outstanding feature of it is the `make` command for `mingw32-make.exe`.

## Getting Started

> Note: In order to use this, you need to have access to use `mklink` command in Windows command prompt. 

1. Get a copy of the `env` folder into your destination directory. You can get it from this repository via clones or downloads (or whatever you prefer). (You are strongly recommended to put the `env` folder in the root of your project directory)
2. Run `env\init.bat` to initialize the environment. (You may then set the name of the environment in the `env\env_name.txt`)
3. All is done! You can now use the `env\activate.bat` to activate the environment and use the `mingw32-make.exe` via the `make` command. (As long as you have MinGW-GCC set in your PATH variable)

To deactivate the environment, simply run `env\deactivate.bat` in the command prompt.

The script `env\deinit.bat` will remove the `env\bin\` directory from disk.
The script `env\reinit.bat` will re-initialize the environment.

<details>
    <summary><b>Advanced Tutorial of Getting Started</b></summary><br>
    If you want to make the <code>env</code>, which is under root directory, be able to be updated with git, you can follow these extra steps:<br>
    <ol>
        <li>You may clone this repository into somewhere, like <code>keep_local\WinEnv4MinGW-GCC</code> under the root directory.</li>
        <li>Execute <code>mklink /J env .\keep_local\WinEnv4MinGW-GCC\env</code> under the root directory.</li>
        <li>Now you can update the <code>env</code> folder with git under <code>.\keep_local\WinEnv4MinGW-GCC\</code>.</li>
    </ol>
</details>

## Notes

- If you're working on a disk with different drive letter from time to time, you may need to run `env\reinit.bat` every time it changes.
- If you're working on multiple MinGW-GCC versions, you may need to run `env\reinit.bat` every time you switch to a new version.

## Working Principle

- Script `env\init.bat` will create a new directory `env\bin\` and use `which` and `mklink` to create symbolic links to the MinGW-GCC executables.
- Script `env\activate.bat` will add the `env\bin\` directory to the PATH environment variable.
- Script `env\deactivate.bat` will remove the `env\bin\` directory from the PATH environment variable.
- Script `env\deinit.bat` will remove the `env\bin\` directory from disk.
- Script `env\reinit.bat` will delete the `env\bin\` directory's contents and re-initialize the environment.

