#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */

int main(int argc, char const *argv[]) {
    struct sockaddr_in self;
    memset(&self, 0, sizeof(self));
    self.sin_family = AF_INET;
    self.sin_port = htons(7788);
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    int ret;
    ret = bind(udp_socket, (const struct sockaddr *)&self, sizeof(self));
    if (ret == -1) {
        perror("error");
        return -1;
    }
    while (1) {
        getchar();
    }

    return 0;
}
