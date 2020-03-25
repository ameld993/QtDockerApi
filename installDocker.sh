#/usr/bin

sudo apt-get update
sudo apt-get -y upgrade

sudo apt-get install -y docker docker.io 


sudo cp DockerD.service /etc/systemd/system/DockerD.service
sudo systemctl start DockerD.service
sudo systemctl enable DockerD.service