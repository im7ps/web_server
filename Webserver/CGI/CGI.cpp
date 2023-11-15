/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgerace <sgerace@student.42.fr>              +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:58:08 by sgerace            #+#    #+#             */
/*   Updated: 2023/11/12 11:21:02 by sgerace           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CGI.hpp"
#include <dirent.h>

CGI::CGI()
{
	this->path_info = "";
}

CGI::~CGI()
{
	
}

void CGI::get_file_path(Request& request)
{
	char path_info[1024];

	//DIR *dir = opendir(request.dir_path.c_str());

	DIR *dir = opendir("."); //questa è solo per i test, quando i file saranno nella directory /var/www/ si dovrà usare quello commentato sopra
    if (dir == NULL)
	{
        perror("Errore durante l'apertura della directory corrente");
        return ;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
	{
        // Verifica se il nome del file termina con ".php"
        if (strstr(entry->d_name, ".php") != NULL)
		{
            strcpy(path_info, ".");
            strcat(path_info, "/");
            strcat(path_info, entry->d_name);

            // Ora 'path_info' contiene il percorso completo del file .php
            printf("Percorso completo del file .php: %s\n", path_info);
			break ;
        }
    }
    closedir(dir);
	this->path_info = path_info;
	return ;
}

int CGI::exec_cgi(Request& request)
{
	std::cout << "Executing CGI" << std::endl;
	this->get_file_path(request);

	// Determina il percorso completo come PATH_INFO
	std::string compliant = "/var/www/html/test.php";
    const char* requestedPath = compliant.c_str(); // Sostituisci con il percorso effettivo
    const char* pathInfo = requestedPath;

	std::string env_path = "PATH_INFO=/var/www/html/test.php";

    // Imposta le variabili di ambiente
    char* envVars[] = {
        const_cast<char*>(env_path.c_str()),
        // Aggiungi altre variabili di ambiente se necessario
        NULL
    };

    // Definisci gli argomenti per l'esecuzione di PHP-CGI
    char* phpArgs[] = {(char*)"/usr/bin/php-cgi", const_cast<char*>(pathInfo), NULL};

    // Crea una pipe per la comunicazione tra processi
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

	long long start_time = gettimems();

    // Fork per creare un processo figlio
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Questo è il processo figlio
		std::cout << "Processo figlio" << std::endl;
        // Chiudi l'estremità di lettura della pipe
        close(pipefd[0]);

        // Reindirizza lo stdout al lato scrittura della pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        // Esegui PHP-CGI con execve
        execve("/usr/bin/php-cgi", const_cast<char* const*>(phpArgs), envVars);

        // Se execve restituisce, c'è stato un errore
        perror("execve");
        _exit(EXIT_FAILURE);
    } else {
		close(pipefd[1]);
		// Questo è il processo padre
		std::cout << "Processo padre\n" << std::endl;
		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(pipefd[0], &read_fds);

		struct timeval timeout;
		timeout.tv_sec = 5;  // Timeout di 2 secondi (modifica a seconda delle tue esigenze)
		timeout.tv_usec = 0;

		char buffer[4096];
		while (true) {
            // Usa select per controllare se ci sono dati da leggere
            int result = select(pipefd[0] + 1, &read_fds, NULL, NULL, &timeout);

            if (result == -1) {
                perror("select");
                break;
            } else if (result == 0) {
                // Timeout scaduto
                std::cout << "Timeout scaduto nel processo padre" << std::endl;
                break;
            } else {
                // Ci sono dati da leggere
                ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));

                if (bytesRead > 0) {
                    // Dati ricevuti dal processo figlio, puoi gestirli come desiderato
                    std::cout << "Dati ricevuti: " << std::string(buffer, bytesRead) << std::endl;
                }

                // Verifica se il processo figlio è terminato
                int status;
                pid_t result = waitpid(pid, &status, WNOHANG);

                if (result == -1) {
                    perror("waitpid");
                    break;
                } else if (result > 0) {
                    // Il processo figlio è terminato, esci dal loop
                    std::cout << "Il processo figlio è terminato" << std::endl;
                    break;
                }
            }
        }
        close(pipefd[0]);
    }	
    return 0;
}