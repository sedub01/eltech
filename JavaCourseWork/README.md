# JavaCourseWork
Курсовая по Java

Делал с помощью VSCode

Для демонстрации введите в командой консоли:

```>java -cp .\target\coursework-1.0-SNAPSHOT.jar MyPC```

Текст для генерации БД:

```SQL
CREATE SCHEMA IF NOT EXISTS `coursework` DEFAULT CHARACTER SET utf8 ;
USE `coursework` ;

CREATE TABLE IF NOT EXISTS `team` (
  `id` INT PRIMARY KEY,
  `wins` INT,
  `losses` INT,
  `games` INT);

CREATE TABLE IF NOT EXISTS `footballers` (
  `id` INT PRIMARY KEY AUTO_INCREMENT,
  `name` VARCHAR(45),
  `lastname` VARCHAR(45),
  `club` VARCHAR(45),
  `city` VARCHAR(45),
  `goals` INT,
  `salary` INT,
  `roleid` INT, 
  `bossid` INT, 
  FOREIGN KEY (bossid) REFERENCES team(id) ON DELETE SET NULL)
  AUTO_INCREMENT = 1200;

CREATE TABLE IF NOT EXISTS `calendar` (
  `id` INT PRIMARY KEY AUTO_INCREMENT,
  `date` VARCHAR(45),
  `wins` INT,
  `losses` INT,
  `bossid` INT,
  FOREIGN KEY (bossid) REFERENCES team(id) ON DELETE SET NULL)
AUTO_INCREMENT = 1;

INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1200', 'Билли', 'Херрингтон', 'ЦСКА', 'Москва', '2', '10000', '0');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1201', 'Антон', 'Чехов', 'Зенит', 'Санкт-Петербург', '3', '12000', '0');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1202', 'Игорь', 'Прихожин', 'ЦСКА', 'Екатеринбург', '4', '14000', '1');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1203', 'Семен', 'Пахомов', 'Спартак', 'Красноярск', '5', '16000', '1');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1204', 'Андрей', 'Парещенков', 'Динамо', 'Вильнюс', '6', '18000', '2');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1205', 'Гай', 'Юлий', 'СПКР', 'Рим', '7', '20000', '2');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1206', 'Иван', 'Любимов', 'ЦСКА', 'Торжков', '8', '22000', '3');
INSERT INTO `footballers` (`id`, `name`, `lastname`, `club`, `city`, `goals`, `salary`, `roleid`) VALUES ('1207', 'Арнольд', 'Шварцниггер', 'Зенит', 'Минск', '9', '24000', '3');

INSERT INTO `team` (`id`, `wins`, `losses`, `games`) VALUES ('222123', '3', '2', '7');

INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('1', '12.02.1973', '0', '1');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('2', '14.02.1973', '2', '3');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('3', '16.02.1973', '4', '2');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('4', '19.02.1973', '3', '3');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('5', '27.02.1973', '4', '0');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('6', '02.03.1973', '2', '1');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('7', '12.03.1973', '1', '3');
INSERT INTO `calendar` (`id`, `date`, `wins`, `losses`) VALUES ('8', '14.03.1973', '2', '2');
```
