# BitNCrypt ![Star](https://img.shields.io/github/stars/JayNakum/BitNCrypt?style=social)
An easy to use, simple and effective command line tool for password management.

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/JayNakum/BitNCrypt?include_prereleaseslabel=Download&style=for-the-badge)](https://github.com/JayNakum/BitNCrypt/releases)

## Some Examples 
    pf2u$o43P6#  
    l6#Uq4Lp4R2  
    i2Pu$f4g$T  

## How to setup?
- Download the *BitNCrypt.exe* file.
- Create a *key.txt* file in the same directory as *BitNCrypt.exe*.
- Put the lyrics of your favorite song in the *key.txt* file and make sure to **not share** it with anyone.
- [OPTIONAL] Set the environment path if you wish to use the tool from any directory.
- Run ```bitncrypt -generate```. It will *prepare the key.txt*. And it will also provide an **optional key** for you to remember.

## How to use?
- Run ```bitncrypt -get <keyword>```. Here the *keyword* can be anything. Just make sure to use different keyword for different passwords.
    - For example, you can use the *github+your@email* as a keyword.
- Enter your prefered **6 digit key**.
- It will directly copy the password to the clipboard.
- If you wish to *display* the password in the console, add ```-display``` after ```-get```.

## Future Plans
- Implement better algorithms

Developed by [Jay Nakum](https://JayNakum.github.io)