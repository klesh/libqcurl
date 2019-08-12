FROM ubuntu:18.04
#FROM debian:9.5

COPY sources.ubu.list /etc/apt
#COPY sources.deb.list /etc/apt

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    openssh-server

RUN useradd -m sftpuser
RUN echo "sftpuser:sftppass" | chpasswd

RUN useradd -m sftpkey
RUN mkdir /home/sftpkey/.ssh
RUN chmod 700 /home/sftpkey/.ssh
COPY id_rsa.pub /home/sftpkey/.ssh/authorized_keys
RUN chmod 600 /home/sftpkey/.ssh/authorized_keys

COPY sftpkey/hello.txt /home/sftpkey
COPY sftpuser/foobar.txt /home/sftpuser

RUN chown -R sftpkey:sftpkey /home/sftpkey
RUN chown -R sftpuser:sftpuser /home/sftpuser

COPY entry.sh /
RUN chmod +x entry.sh

ENTRYPOINT ["/entry.sh"]
