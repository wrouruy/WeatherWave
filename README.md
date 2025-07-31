## How to Use the App?
1. Clone the repository: ``` git clone https://github.com/wrouruy/WeatherWave.git && cd WeatherWave ```
2. Install libraries:
```
apt     : sudo apt install libcurl4-openssl-dev libcjson-dev
packman : sudo pacman -S curl cjson
dnf     : sudo dnf install libcurl-devel cjson-devel
brew    : brew install curl
```
3. Compile the code: ``` clang -o WeatherWave main.c -lcurl -lcjson ```
4. Run the compiled code: ``` ./WeatherWave "your city" ```

Thank you for reading☺️!
