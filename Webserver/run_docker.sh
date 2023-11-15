sudo docker rm -f $(sudo docker ps -a -q)
sudo docker build -t web_server .
sudo docker run -p 8080:8080 --net=host -d web_server
sudo docker logs -f $(sudo docker ps -q)