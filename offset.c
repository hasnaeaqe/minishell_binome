#include <libc.h>

int main()
{
    int fd1 = open("fichier.txt", O_RDONLY);
int fd2 = dup(fd1); // fd2 = 10 maintenant pointe vers la même file description que fd1

printf("Offset avant lecture: %ld\n", lseek(fd1, 0, SEEK_CUR)); // affiche 0

char buf[10];

read(fd1, buf, 5); // lit 5 octets via fd1 → offset devient 5
buf[6] = '\0';
printf("Offset après read(fd1): %ld\n", lseek(fd1, 0, SEEK_CUR)); // affiche 5
printf("buffer : %s\n", buf); // affiche 5

read(fd2, buf, 5); // lit 5 octets via fd2 → offset devient 10
printf("Offset après read(fd2): %ld\n", lseek(fd1, 0, SEEK_CUR)); // affiche 10 !!
printf("buffer : %s\n", buf); // affiche 5
}