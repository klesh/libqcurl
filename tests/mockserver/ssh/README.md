# Login info of sftpuser
username: sftpuser
password: sftppass

# Login info of sftpkey
username: sftpkey
privatekey: id_rsa
privatekey password: pass


# Build image
docker build -t mock-sshd .

# Run docker
docker run -it --rm --name mock-sshd -p 7882:22 mock-sshd

# Known issue:
`libssh2 v1.8.2` would not function when key files located other than `~/.ssh`
Solution: use `v1.9.0`
