
# 0) Xoá bản clone lỗi

cd $env:USERPROFILE\Desktop\ATK-DEF

Remove-Item -Recurse -Force .\CTF-Wups

# 1) Clone KHÔNG checkout

git clone --no-checkout https://github.com/uchihashisuite/CTF-Wups.git CTF-Wups

cd .\CTF-Wups

# 2) Bật sparse-checkout và CHỈ lấy thư mục đích

git sparse-checkout init --cone

git sparse-checkout set SVATTT204/ATK-DEF

# 3) Checkout nhánh main (giờ sẽ không đụng các file “cấm”)

git checkout main

# 4) Copy 2 folder vào đúng chỗ

mkdir -Force SVATTT204\ATK-DEF

Copy-Item -Recurse -Force "$env:USERPROFILE\Desktop\ATK-DEF\Web1" "SVATTT204\ATK-DEF\Web1"

Copy-Item -Recurse -Force "$env:USERPROFILE\Desktop\ATK-DEF\Web2" "SVATTT204\ATK-DEF\Web2"

# 5) Bật Git LFS cho file .jar trước khi add

git lfs install

git lfs track "*.jar"

git add .gitattributes

# 6) (Nếu chưa cấu hình danh tính)

git config --global user.name "uchi******"

git config --global user.email "mbs******"


# 7) Add/commit/push

git add SVATTT204/ATK-DEF/Web1 SVATTT204/ATK-DEF/Web2

git commit -m "Add Web1 & Web2 into SVATTT204/ATK-DEF"

git push origin main
