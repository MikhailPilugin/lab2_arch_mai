CREATE TABLE IF NOT EXISTS `User` 
(
    `id` INT NOT NULL AUTO_INCREMENT,
    `first_name` VARCHAR(256) NOT NULL,
    `last_name` VARCHAR(256) NOT NULL,
    `login` VARCHAR(256) NOT NULL UNIQUE,
    `password` VARCHAR(256) NOT NULL,
    `email` VARCHAR(256) NULL,
    `title` VARCHAR(1024) NULL,

    PRIMARY KEY (`id`),
    KEY `fn` (`first_name`),
    KEY `ln` (`last_name`)
);

CREATE TABLE IF NOT EXISTS `Report` 
(
    `id` INT NOT NULL AUTO_INCREMENT,
    `name` VARCHAR(256) NOT NULL,
    `type` VARCHAR(256) NOT NULL,
    `description` VARCHAR(1024) NULL,
    `author` VARCHAR(256) NOT NULL,

    PRIMARY KEY (`id`),
    KEY `n` (`name`)
);

CREATE TABLE IF NOT EXISTS `Conference` 
(
    `id` INT NOT NULL AUTO_INCREMENT,
    `reportId` INT NOT NULL,
    `userId` INT NOT NULL,

    PRIMARY KEY (`id`),
    FOREIGN KEY (`reportId`) REFERENCES Report (`id`),
    FOREIGN KEY (`userId`) REFERENCES User (`id`)
);



INSERT INTO `User` (`first_name`, `last_name`, `email`, `title`, `login`, `password`) VALUES
("User1", "Userov1", "mail1@mail.ru", "Mister", "log1", "123"),
("User2", "Userov2", "mail2@mail.ru", "Mister", "log2", "123"),
("User3", "Userov3", "mail3@mail.ru", "Mister", "log3", "123");

INSERT INTO `Report` (`name`, `type`, `author`, `description`) VALUES
("Great report1", "Science", "Petr Petrov", "Report about great report"),
("Great report2", "Science", "Vasya Ivanov", "Report about great report"),
("Great report3", "Science", "Daniil Danilov", "Report about great report"),
("Great report4", "Science", "Elena Prekrasnaya", "Report about great report"),
("Great report5", "Science", "Ekaterina Premudraya", "Report about great report"),
("Great report6", "Science", "Imya Familiya", "Report about great report"),
("Great report7", "Science", "Top Secret", "Report about great report");

INSERT INTO `Conference` (`userId`, `reportId`) VALUES
(1, 3),
(3, 4),
(3, 5);