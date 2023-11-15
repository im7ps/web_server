#download alpine base
FROM alpine:latest

#download cpp dev tools and make
RUN apk add --no-cache build-base cmake
# Aggiorna i pacchetti e installa PHP e php-cgi
RUN apk update && apk add php-cgi
#copy all source code to Documents
COPY . /Documents/funny
#set working directory
WORKDIR /Documents/funny

#create directories
RUN mkdir -p /var/www/html
#create file test.php in /var/www/html
RUN echo '<?php echo "hello world"; sleep(10000); ?>' > /var/www/html/test.php
#compile and run
RUN ["make", "re"]
# CMD [ "ls", "-la" ]
CMD [ "./web_server", "configuration_files/full_nginx_example.conf" ]
EXPOSE 8080

#sh docker build -t web_server .
#sudo docker run --net=host -d web_server