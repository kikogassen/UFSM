CREATE TABLE `cargo` (
  `id_cargo` int(11) NOT NULL AUTO_INCREMENT,
  `nome_cargo` varchar(50) NOT NULL,
  PRIMARY KEY (`id_cargo`)
) AUTO_INCREMENT=0;

INSERT INTO `cargo` (`id_cargo`, `nome_cargo`) VALUES
	(1, 'Aluno'),
	(2, 'Professor'),
	(3, 'Funcionário'),
	(4, 'Visitante');

CREATE TABLE `estacionamento` (
  `id_estacionamento` int(11) NOT NULL AUTO_INCREMENT,
  `nome_estacionamento` varchar(50) NOT NULL,
  `vagas_estacionamento` int(11) NOT NULL,
  `vagas_ocupadas_estacionamento` int(11) NOT NULL,
  PRIMARY KEY (`id_estacionamento`)
) AUTO_INCREMENT=1;

CREATE TABLE `usuario` (
  `id_usuario` int(11) NOT NULL AUTO_INCREMENT,
  `id_cargo` int(11) NOT NULL DEFAULT '0',
  `nome_usuario` varchar(50) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id_usuario`),
  KEY `fk_cargo_usuario` (`id_cargo`),
  CONSTRAINT `fk_cargo_usuario` FOREIGN KEY (`id_cargo`) REFERENCES `cargo` (`id_cargo`) ON DELETE NO ACTION ON UPDATE NO ACTION
) AUTO_INCREMENT=1;

CREATE TABLE `veiculo` (
  `placa_veiculo` varchar(8) NOT NULL,
  `id_usuario` int(11) DEFAULT NULL,
  PRIMARY KEY (`placa_veiculo`),
  KEY `fk_veiculo_usuario` (`id_usuario`),
  CONSTRAINT `fk_veiculo_usuario` FOREIGN KEY (`id_usuario`) REFERENCES `usuario` (`id_usuario`) ON DELETE NO ACTION ON UPDATE NO ACTION
);

CREATE TABLE `estacionada` (
  `placa_veiculo` varchar(8) NOT NULL DEFAULT '0',
  `id_estacionamento` int(11) NOT NULL DEFAULT '0',
  `datahora_entrada_estacionada` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `datahora_saida_estacionada` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`placa_veiculo`,`datahora_entrada_estacionada`),
  KEY `fk_estacionamento_estacionada` (`id_estacionamento`),
  CONSTRAINT `fk_estacionamento_estacionada` FOREIGN KEY (`id_estacionamento`) REFERENCES `estacionamento` (`id_estacionamento`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_veiculo_estacionada` FOREIGN KEY (`placa_veiculo`) REFERENCES `veiculo` (`placa_veiculo`) ON DELETE NO ACTION ON UPDATE NO ACTION
);

INSERT INTO `estacionamento` (`id_estacionamento`, `nome_estacionamento`, `vagas_estacionamento`, `vagas_ocupadas_estacionamento`) VALUES
	(1, 'Estacionamento 1', 100, 0),
	(2, 'Estacionamento 2', 200, 0),
	(3, 'Estacionamento 3', 300, 0),
	(4, 'Estacionamento 4', 400, 0),
	(5, 'Estacionamento 5', 500, 0);

INSERT INTO `usuario` (`id_usuario`, `id_cargo`, `nome_usuario`) VALUES
	(3, 4, 'Visitante');

CREATE TABLE `vagas_disponiveis` (
	`id_estacionamento` INT(11) NOT NULL,
	`nome_estacionamento` VARCHAR(50) NOT NULL,
	`vagas_disponiveis` BIGINT(12) NOT NULL
);

INSERT INTO `veiculo` (`placa_veiculo`, `id_usuario`) VALUES
	('XXX-0000', 3);

DELIMITER //
CREATE TRIGGER `entrada_carro` AFTER INSERT ON `estacionada` FOR EACH ROW BEGIN
	UPDATE estacionamento SET vagas_ocupadas_estacionamento = vagas_ocupadas_estacionamento + 1 WHERE id_estacionamento = NEW.id_estacionamento;
END//

CREATE TRIGGER `saida_carro` AFTER UPDATE ON `estacionada` FOR EACH ROW BEGIN
	UPDATE estacionamento SET vagas_ocupadas_estacionamento = vagas_ocupadas_estacionamento - 1 WHERE id_estacionamento = NEW.id_estacionamento;
END//
DELIMITER ;

CREATE VIEW `mostra_vagas_disponiveis` AS select `estacionamento`.`id_estacionamento` AS `id_estacionamento`,`estacionamento`.`nome_estacionamento` AS `nome_estacionamento`,(`estacionamento`.`vagas_estacionamento` - `estacionamento`.`vagas_ocupadas_estacionamento`) AS `vagas_disponiveis` from `estacionamento`;