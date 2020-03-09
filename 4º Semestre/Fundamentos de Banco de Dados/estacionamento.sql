-- --------------------------------------------------------
-- Servidor:                     127.0.0.1
-- Versão do servidor:           5.5.60 - MySQL Community Server (GPL)
-- OS do Servidor:               Win64
-- HeidiSQL Versão:              9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Copiando estrutura do banco de dados para estacionamento_universitario
CREATE DATABASE IF NOT EXISTS `estacionamento_universitario` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `estacionamento_universitario`;

-- Copiando estrutura para tabela estacionamento_universitario.cargo
DROP TABLE IF EXISTS `cargo`;
CREATE TABLE IF NOT EXISTS `cargo` (
  `id_cargo` int(11) NOT NULL AUTO_INCREMENT,
  `nome_cargo` varchar(50) NOT NULL,
  PRIMARY KEY (`id_cargo`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- Copiando dados para a tabela estacionamento_universitario.cargo: ~4 rows (aproximadamente)
DELETE FROM `cargo`;
/*!40000 ALTER TABLE `cargo` DISABLE KEYS */;
INSERT INTO `cargo` (`id_cargo`, `nome_cargo`) VALUES
	(1, 'Aluno'),
	(2, 'Professor'),
	(3, 'Funcionário'),
	(4, 'Visitante');
/*!40000 ALTER TABLE `cargo` ENABLE KEYS */;

-- Copiando estrutura para tabela estacionamento_universitario.estacionada
DROP TABLE IF EXISTS `estacionada`;
CREATE TABLE IF NOT EXISTS `estacionada` (
  `placa_veiculo` varchar(8) NOT NULL DEFAULT '0',
  `id_estacionamento` int(11) NOT NULL DEFAULT '0',
  `datahora_entrada_estacionada` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `datahora_saida_estacionada` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`placa_veiculo`,`datahora_entrada_estacionada`),
  KEY `fk_estacionamento_estacionada` (`id_estacionamento`),
  CONSTRAINT `fk_estacionamento_estacionada` FOREIGN KEY (`id_estacionamento`) REFERENCES `estacionamento` (`id_estacionamento`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_veiculo_estacionada` FOREIGN KEY (`placa_veiculo`) REFERENCES `veiculo` (`placa_veiculo`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Copiando estrutura para tabela estacionamento_universitario.estacionamento
DROP TABLE IF EXISTS `estacionamento`;
CREATE TABLE IF NOT EXISTS `estacionamento` (
  `id_estacionamento` int(11) NOT NULL AUTO_INCREMENT,
  `nome_estacionamento` varchar(50) NOT NULL,
  `vagas_estacionamento` int(11) NOT NULL,
  `vagas_ocupadas_estacionamento` int(11) NOT NULL,
  PRIMARY KEY (`id_estacionamento`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- Copiando dados para a tabela estacionamento_universitario.estacionamento: ~5 rows (aproximadamente)
DELETE FROM `estacionamento`;
/*!40000 ALTER TABLE `estacionamento` DISABLE KEYS */;
INSERT INTO `estacionamento` (`id_estacionamento`, `nome_estacionamento`, `vagas_estacionamento`, `vagas_ocupadas_estacionamento`) VALUES
	(1, 'Estacionamento 1', 100, 0),
	(2, 'Estacionamento 2', 200, 0),
	(3, 'Estacionamento 3', 300, 0),
	(4, 'Estacionamento 4', 400, 0),
	(5, 'Estacionamento 5', 500, 0);
/*!40000 ALTER TABLE `estacionamento` ENABLE KEYS */;

-- Copiando estrutura para tabela estacionamento_universitario.usuario
DROP TABLE IF EXISTS `usuario`;
CREATE TABLE IF NOT EXISTS `usuario` (
  `id_usuario` int(11) NOT NULL AUTO_INCREMENT,
  `id_cargo` int(11) NOT NULL DEFAULT '0',
  `nome_usuario` varchar(50) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id_usuario`),
  KEY `fk_cargo_usuario` (`id_cargo`),
  CONSTRAINT `fk_cargo_usuario` FOREIGN KEY (`id_cargo`) REFERENCES `cargo` (`id_cargo`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

-- Copiando dados para a tabela estacionamento_universitario.usuario: ~3 rows (aproximadamente)
DELETE FROM `usuario`;
/*!40000 ALTER TABLE `usuario` DISABLE KEYS */;
/*!40000 ALTER TABLE `usuario` ENABLE KEYS */;

-- Copiando estrutura para view estacionamento_universitario.vagas_disponiveis
DROP VIEW IF EXISTS `vagas_disponiveis`;
-- Criando tabela temporária para evitar erros de dependência de VIEW
CREATE TABLE `vagas_disponiveis` (
	`id_estacionamento` INT(11) NOT NULL,
	`nome_estacionamento` VARCHAR(50) NOT NULL COLLATE 'utf8_general_ci',
	`vagas_disponiveis` BIGINT(12) NOT NULL
) ENGINE=MyISAM;

-- Copiando estrutura para tabela estacionamento_universitario.veiculo
DROP TABLE IF EXISTS `veiculo`;
CREATE TABLE IF NOT EXISTS `veiculo` (
  `placa_veiculo` varchar(8) NOT NULL,
  `id_usuario` int(11) DEFAULT NULL,
  PRIMARY KEY (`placa_veiculo`),
  KEY `fk_veiculo_usuario` (`id_usuario`),
  CONSTRAINT `fk_veiculo_usuario` FOREIGN KEY (`id_usuario`) REFERENCES `usuario` (`id_usuario`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Copiando dados para a tabela estacionamento_universitario.veiculo: ~2 rows (aproximadamente)
DELETE FROM `veiculo`;
/*!40000 ALTER TABLE `veiculo` DISABLE KEYS */;
INSERT INTO `veiculo` (`placa_veiculo`, `id_usuario`) VALUES
	('XXX-0000', 3);
/*!40000 ALTER TABLE `veiculo` ENABLE KEYS */;

-- Copiando estrutura para trigger estacionamento_universitario.entrada_carro
DROP TRIGGER IF EXISTS `entrada_carro`;
SET @OLDTMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
DELIMITER //
CREATE TRIGGER `entrada_carro` AFTER INSERT ON `estacionada` FOR EACH ROW BEGIN
	UPDATE estacionamento SET vagas_ocupadas_estacionamento = vagas_ocupadas_estacionamento + 1 WHERE id_estacionamento = NEW.id_estacionamento;
END//
DELIMITER ;
SET SQL_MODE=@OLDTMP_SQL_MODE;

-- Copiando estrutura para trigger estacionamento_universitario.saida_carro
DROP TRIGGER IF EXISTS `saida_carro`;
SET @OLDTMP_SQL_MODE=@@SQL_MODE, SQL_MODE='STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
DELIMITER //
CREATE TRIGGER `saida_carro` AFTER UPDATE ON `estacionada` FOR EACH ROW BEGIN
	UPDATE estacionamento SET vagas_ocupadas_estacionamento = vagas_ocupadas_estacionamento - 1 WHERE id_estacionamento = NEW.id_estacionamento;
END//
DELIMITER ;
SET SQL_MODE=@OLDTMP_SQL_MODE;

-- Copiando estrutura para view estacionamento_universitario.vagas_disponiveis
DROP VIEW IF EXISTS `vagas_disponiveis`;
-- Removendo tabela temporária e criando a estrutura VIEW final
DROP TABLE IF EXISTS `vagas_disponiveis`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `vagas_disponiveis` AS select `estacionamento`.`id_estacionamento` AS `id_estacionamento`,`estacionamento`.`nome_estacionamento` AS `nome_estacionamento`,(`estacionamento`.`vagas_estacionamento` - `estacionamento`.`vagas_ocupadas_estacionamento`) AS `vagas_disponiveis` from `estacionamento`;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
