SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
SET SQL_SAFE_UPDATES = 0;
 
CREATE SCHEMA HPoS ;
USE HPoS ;
 
-- Table Role 
 
CREATE TABLE Role (
 roleID INT NOT NULL AUTO_INCREMENT,
 roleType NVARCHAR(45) NOT NULL,
 PRIMARY KEY (roleID)
);
 
-- Table User 
 
CREATE TABLE User (
 userID INT NOT NULL AUTO_INCREMENT,
 username  NVARCHAR(20) NOT NULL unique,
 pwd NVARCHAR(20) NOT NULL,
 pinCode INT NOT NULL unique,
 lastName NVARCHAR(15) NOT NULL,
 firstName NVARCHAR(15) NOT NULL,
 age INT NULL,
 DOB DATE NULL,
 idCard NVARCHAR(15) NULL,
 phone NVARCHAR(15) NULL,
 roleID INT NOT NULL,
 PRIMARY KEY (userID),
 CONSTRAINT fk_User_Role 
 FOREIGN KEY (roleID)
 REFERENCES Role (roleID)
);


-- Table Invoice 
 
CREATE TABLE Invoice (
 ivID INT NOT NULL AUTO_INCREMENT,
 userID INT NOT NULL,
 ivdate DATE NOT NULL,
 ivtime TIME NOT NULL,
 total DOUBLE NOT NULL,
 tax FLOAT NOT NULL,
 discount FLOAT NOT NULL,
 payment DOUBLE NOT NULL,
 PRIMARY KEY (ivID),
 CONSTRAINT fk_Invoice_User 
 FOREIGN KEY (userID)
 REFERENCES User (userID)
);


 
-- Table Product 
 
CREATE TABLE Product (
 proID INT NOT NULL AUTO_INCREMENT,
 proName NVARCHAR(25) NOT NULL,
 proPrice DOUBLE NOT NULL,
 proDes NVARCHAR (255) NULL,
 PRIMARY KEY (proID)
);

-- Table Picture 
 
CREATE TABLE Picture (
 picID INT NOT NULL AUTO_INCREMENT,
 picUrl NVARCHAR(200) NOT NULL,
 proID INT NULL,
 userID INT NULL,
 PRIMARY KEY (picID),
 CONSTRAINT fk_Picture_Product
 FOREIGN KEY (proID)
 REFERENCES Product (proID),
 CONSTRAINT fk_Picture_User
 FOREIGN KEY (proID)
 REFERENCES User(userID)
 );
 
-- Table InvoiceDetail 
 
CREATE TABLE InvoiceDetail (
 dtID INT NOT NULL AUTO_INCREMENT,
 ivID INT NOT NULL,
 proID INT NOT NULL,
 quantity INT NOT NULL,
 total INT NOT NULL,
 PRIMARY KEY (dtID),
 CONSTRAINT fk_InvoiceDetail_Product
 FOREIGN KEY (proID)
 REFERENCES Product (proID),
 CONSTRAINT fk_InvoiceDetail_Invoice 
 FOREIGN KEY (ivID)
 REFERENCES Invoice (ivID)
);
-- Table History
create table History(
historyID INT NOT NULL,
actionTypeID INT NOT NULL,
historyTime time not null,
historyDescription nvarchar(150) NULL,
userID INT NOT NULL,
primary key (historyID),
constraint fk_History_User
foreign key (userID)
references User(userID),
constraint fk_History_ActionType
foreign key (actionTypeID)
references ActionType(actionTypeID)
);

-- Table History_Type
create table ActionType(
actionTypeID INT NOT NULL AUTO_INCREMENT,
actionType nvarchar(50) NOT NULL,
actionDescription nvarchar(150) NULL,
primary key (actionTypeID)
);

-- Table Country

create table Country(
countryPrefix nvarchar(10) not null,
countryName nvarchar(10) not null,
description NVARCHAR(200) null,
primary key(countryPrefix)
);
  
 
-- Table QualityStandard 
 
-- CREATE TABLE QualityStandard (
--  standardID INT NOT NULL AUTO_INCREMENT,
--  standardName NVARCHAR(25) NOT NULL,
--  description NVARCHAR(255) NULL,
--  PRIMARY KEY (standardID)
-- );
 
-- Table Attribute 
 
-- CREATE TABLE Attribute (
--  attID INT NOT NULL AUTO_INCREMENT,
--  attName NVARCHAR(45) NOT NULL,
--  attDes NVARCHAR(250) NOT NULL,
--  PRIMARY KEY (attID)
-- 
-- );
 
-- Table Manufacturer 
 
CREATE TABLE Manufacturer (
 manuPrefix nvarchar(10) NOT NULL,
 manuName NVARCHAR(45) NOT NULL,
 address NVARCHAR(205) NULL,
 phone NVARCHAR(15) NULL,
 logo NVARCHAR(200) NULL,
 PRIMARY KEY (manuPrefix)
);


-- Table Barcode
  
create table Barcode(
barcodeID INT not null AUTO_INCREMENT,
proID INT NOT NULL,
countryPrefix nvarchar(10) not null,
manuPrefix nvarchar(10) not null,
productPrefix nvarchar(10) not null unique,
checkDigit INT NULL,
imDate DATE NOT NULL,
imTime TIME NOT NULL,
primary key(barcodeID),
constraint fk_Barcode_Country
foreign key (countryPrefix)
references Country (countryPrefix),
constraint fk_Barcode_Manufacturer
foreign key (manuPrefix)
references Manufacturer (manuPrefix),
constraint fk_Barcode_Product
foreign key (proID)
references Product (proID)
);
-- Table Category 
 
CREATE TABLE Category (
 ctID INT NOT NULL AUTO_INCREMENT,
 ctName NVARCHAR(45) NOT NULL,
 PRIMARY KEY (ctID)
 );
 

  


-- Table Product_has_QualityStandard 
 
-- CREATE TABLE Product_has_QualityStandard (
--  Product_proID INT NOT NULL,
--  QualityStandard_standardID INT NOT NULL,
--  PRIMARY KEY (Product_proID , QualityStandard_standardID),
--  CONSTRAINT fk_Product_has_QualityStandard_Product 
--  FOREIGN KEY (Product_proID)
--  REFERENCES Product (proID),
--  CONSTRAINT fk_Product_has_QualityStandard_Quality
--  FOREIGN KEY (QualityStandard_standardID)
--  REFERENCES QualityStandard (standardID)
-- );
 
-- Table Product_has_Attribute 
 
-- CREATE TABLE Product_has_Attribute (
--  Product_proID INT NOT NULL,
--  Attribute_attID INT NOT NULL,
--  PRIMARY KEY (Product_proID , Attribute_attID),
--  CONSTRAINT fk_Product_has_Attribute_Product 
--  FOREIGN KEY (Product_proID)
--  REFERENCES Product (proID),
--  CONSTRAINT fk_Product_has_Attribute_Attribute 
--  FOREIGN KEY (Attribute_attID)
--  REFERENCES Attribute (attID)
-- );
 
-- Table Picture_has_Product 
 
-- CREATE TABLE Picture_has_Product (
--  Picture_picID INT NOT NULL,
--  Product_proID INT NOT NULL,
--  PRIMARY KEY (Picture_picID , Product_proID),
--  CONSTRAINT fk_Picture_has_Product_Picture 
--  FOREIGN KEY (Picture_picID)
--  REFERENCES Picture (picID),
--  CONSTRAINT fk_Picture_has_Product_Product 
--  FOREIGN KEY (Product_proID)
--  REFERENCES Product (proID)
-- );
 
-- Table Category_has_Product 
 
CREATE TABLE Category_has_Product (
 Category_ctID INT NOT NULL,
 Product_proID INT NOT NULL,
 PRIMARY KEY (Category_ctID , Product_proID),
 CONSTRAINT fk_Category_has_Product_Category 
 FOREIGN KEY (Category_ctID)
 REFERENCES Category (ctID),
 CONSTRAINT fk_Category_has_Product_Product 
 FOREIGN KEY (Product_proID)
 REFERENCES Product (proID)
);
 
-- Table Picture_has_User 
 
-- CREATE TABLE Picture_has_User (
--  Picture_picID INT NOT NULL,
--  User_userID INT NOT NULL,
--  PRIMARY KEY (Picture_picID , User_userID),
--  CONSTRAINT fk_Picture_has_User_Picture 
--  FOREIGN KEY (Picture_picID)
--  REFERENCES Picture (picID),
--  CONSTRAINT fk_Picture_has_User_User 
--  FOREIGN KEY (User_userID)
--  REFERENCES User (userID)
-- );
 
 
 -- INSERT DATA
 
 -- Role data
	
 INSERT INTO Role (roleID, roleType)
 VALUES (NULL, 'Manager');
 INSERT INTO Role (roleID, roleType)
 VALUES (NULL, 'Seller');

 -- User data
 
 INSERT INTO User ( lastname, firstname, DOB, roleID, username,pwd,pincode)
 VALUES ( 'Michael', 'Smith',  '2001-06-02',   '2', 'michael', '123123', '12345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Susan', 'Barker',  '2002-02-22',   '2','susan', '123123', '22345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Robert', 'Tyler',  '2003-06-12',   '2','robert', '123123', '32345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'John', 'Gooding',  '1991-05-03',   '2','john', '123123', '42345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Le', 'Long',  '1991-06-20',   '1','long', '123123', '52345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Helen', 'Fleming',  '1992-06-25',   '2','helen', '123123', '62345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Nguyen', 'Hieu',  '1993-09-21',   '2','hieu', '123123', '72345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Nguyen', 'Hai',  '1994-07-12',   '2','hai', '123123', '82345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Da', 'Mi',  '1995-06-22',   '2','mi', '123123', '92345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Ngo', 'Tien',  '2001-06-2',   '2','tien', '123123', '102345'); 
 INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'Tran', 'Ly',  '1991-06-22',   '2','ly', '123123', '112345'); 

  INSERT INTO User ( lastname, firstname,  DOB,  roleID, username, pwd, pincode)
 VALUES ( 'admin', 'admin',  '1991-06-22',   '2','admin', '123123', '123123');  

-- Insert Company
INSERT INTO `HPoS`.`Manufacturer` (`manuPrefix`, `manuName`, `address`, `phone`, `logo`) VALUES ('4588', 'PepsiCo', '', '', '');

-- Insert ActionType
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Add Inventory');
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Modify Inventory');
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Remove Inventory');
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Add Employee');
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Modify Employee');
INSERT INTO `HPoS`.`ActionType` (`actionType`) VALUES ('Remove Employee');

-- Insert Product 
INSERT INTO `HPoS`.`Product` (`proName`, `proPrice`, `proDes`) VALUES ('Aquafina', '6000', NULL);

-- Insert Barcode
INSERT INTO `HPoS`.`Barcode` (`proID`, `countryPrefix`, `manuPrefix`, `productPrefix`, `checkDigit`, `imDate`, `imTime`) VALUES ('1', '893', '4588', '06305', '3', '2016-10-12', '16:32:00');


-- Insert Category
INSERT INTO `HPoS`.`Category_has_Product` (`Category_ctID`, `Product_proID`) VALUES ('15', '1');

 -- QualityStandard data
 
--  INSERT INTO QualityStandard (standardID, standardName, description)
--  VALUES (NULL, 'ISO 9000','Quality management');
--  INSERT INTO QualityStandard (standardID, standardName, description)
--  VALUES (NULL, 'ISO 14000','Environmental management');
--  INSERT INTO QualityStandard (standardID, standardName, description)
--  VALUES (NULL, 'ISO 45001','Occupational Health and Safety');
--  INSERT INTO QualityStandard (standardID, standardName, description)
--  VALUES (NULL, 'ISO 22000','Food safety management');
 
 -- Attribute data
--  
--  INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Color', 'Blue');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Color', 'Red');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Color', 'Black');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Color', 'White');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Size', 'Small');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Size', 'Normal');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Size', 'Large');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Size', 'Small');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Components', 'Carbon');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Components', 'Glass');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Components', 'Camera');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Components', 'Pin');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Features', 'IOS');
-- INSERT INTO Attribute (attID, attName, attDes)
-- VALUES (NULL, 'Features', 'Android');

-- Manufacturer data

 -- Category data
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Laptop');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Smart Phone');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Beverage');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Food');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Houseware');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Electronic');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Office');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Watches');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Clothing');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Shoes');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Entertaiment');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Book');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Wine');
 INSERT INTO Category (ctID, ctName)
 VALUES (NULL, 'Other');
 INSERT INTO `HPoS`.`Category` (`ctName`) VALUES ('Water');


INSERT INTO Country (countryPrefix, description, countryName) VALUES
('000', 'GS1 US', 'US'),
('001', 'GS1 US', 'US'),
('002', 'GS1 US', 'US'),
('003', 'GS1 US', 'US'),
('004', 'GS1 US', 'US'),
('005', 'GS1 US', 'US'),
('006', 'GS1 US', 'US'),
('007', 'GS1 US', 'US'),
('008', 'GS1 US', 'US'),
('009', 'GS1 US', 'US'),
('010', 'GS1 US - Not used', 'US'),
('011', 'GS1 US', 'US'),
('012', 'GS1 US - Not used', 'US'),
('013', 'GS1 US - Not used', 'US'),
('014', 'GS1 US - Not used', 'US'),
('015', 'GS1 US - Not used', 'US'),
('016', 'GS1 US - Not used', 'US'),
('017', 'GS1 US - Not used', 'US'),
('018', 'GS1 US', 'US'),
('019', 'GS1 US', 'US'),
('020', 'Restricted distribution (MO defined)', ''),
('021', 'Restricted distribution (MO defined)', ''),
('022', 'Restricted distribution (MO defined)', ''),
('023', 'Restricted distribution (MO defined)', ''),
('024', 'Restricted distribution (MO defined)', ''),
('025', 'Restricted distribution (MO defined)', ''),
('026', 'Restricted distribution (MO defined)', ''),
('027', 'Restricted distribution (MO defined)', ''),
('028', 'Restricted distribution (MO defined)', ''),
('029', 'Restricted distribution (MO defined)', ''),
('030', 'GS1 US', 'US'),
('031', 'GS1 US', 'US'),
('032', 'GS1 US', 'US'),
('033', 'GS1 US', 'US'),
('034', 'GS1 US', 'US'),
('035', 'GS1 US', 'US'),
('036', 'GS1 US', 'US'),
('037', 'GS1 US', 'US'),
('038', 'GS1 US', 'US'),
('039', 'GS1 US', 'US'),
('040', 'Restricted distribution (MO defined)', ''),
('041', 'Restricted distribution (MO defined)', ''),
('042', 'Restricted distribution (MO defined)', ''),
('043', 'Restricted distribution (MO defined)', ''),
('044', 'Restricted distribution (MO defined)', ''),
('045', 'Restricted distribution (MO defined)', ''),
('046', 'Restricted distribution (MO defined)', ''),
('047', 'Restricted distribution (MO defined)', ''),
('048', 'Restricted distribution (MO defined)', ''),
('049', 'Restricted distribution (MO defined)', ''),
('050', 'Coupons', ''),
('051', 'Coupons', ''),
('052', 'Coupons', ''),
('053', 'Coupons', ''),
('054', 'Coupons', ''),
('055', 'Coupons', ''),
('056', 'Coupons', ''),
('057', 'Coupons', ''),
('058', 'Coupons', ''),
('059', 'Coupons', ''),
('060', 'GS1 US', 'US'),
('061', 'GS1 US', 'US'),
('062', 'GS1 US', 'US'),
('063', 'GS1 US', 'US'),
('064', 'GS1 US', 'US'),
('065', 'GS1 US', 'US'),
('066', 'GS1 US', 'US'),
('067', 'GS1 US', 'US'),
('068', 'GS1 US', 'US'),
('069', 'GS1 US', 'US'),
('070', 'GS1 US', 'US'),
('071', 'GS1 US', 'US'),
('072', 'GS1 US', 'US'),
('073', 'GS1 US', 'US'),
('074', 'GS1 US', 'US'),
('075', 'GS1 US', 'US'),
('076', 'GS1 US', 'US'),
('077', 'GS1 US', 'US'),
('078', 'GS1 US', 'US'),
('079', 'GS1 US', 'US'),
('080', 'GS1 US', 'US'),
('081', 'GS1 US', 'US'),
('082', 'GS1 US', 'US'),
('083', 'GS1 US', 'US'),
('084', 'GS1 US', 'US'),
('085', 'GS1 US', 'US'),
('086', 'GS1 US', 'US'),
('087', 'GS1 US', 'US'),
('088', 'GS1 US', 'US'),
('089', 'GS1 US', 'US'),
('090', 'GS1 US - Not used', 'US'),
('091', 'GS1 US - Not used', 'US'),
('092', 'GS1 US - Not used', 'US'),
('093', 'GS1 US - Not used', 'US'),
('094', 'GS1 US - Not used', 'US'),
('095', 'GS1 US - Not used', 'US'),
('096', 'GS1 US - Not used', 'US'),
('097', 'GS1 US - Not used', 'US'),
('098', 'GS1 US - Not used', 'US'),
('099', 'GS1 US - Not used', 'US'),
('100', 'GS1 US - Not used', 'US'),
('101', 'GS1 US - Not used', 'US'),
('102', 'GS1 US - Not used', 'US'),
('103', 'GS1 US - Not used', 'US'),
('104', 'GS1 US - Not used', 'US'),
('105', 'GS1 US - Not used', 'US'),
('106', 'GS1 US - Not used', 'US'),
('107', 'GS1 US - Not used', 'US'),
('108', 'GS1 US - Not used', 'US'),
('109', 'GS1 US - Not used', 'US'),
('110', 'GS1 US - Not used', 'US'),
('111', 'GS1 US - Not used', 'US'),
('112', 'GS1 US - Not used', 'US'),
('113', 'GS1 US - Not used', 'US'),
('114', 'GS1 US - Not used', 'US'),
('115', 'GS1 US - Not used', 'US'),
('116', 'GS1 US - Not used', 'US'),
('117', 'GS1 US - Not used', 'US'),
('118', 'GS1 US - Not used', 'US'),
('119', 'GS1 US - Not used', 'US'),
('120', 'GS1 US - Not used', 'US'),
('121', 'GS1 US - Not used', 'US'),
('122', 'GS1 US - Not used', 'US'),
('123', 'GS1 US - Not used', 'US'),
('124', 'GS1 US - Not used', 'US'),
('125', 'GS1 US - Not used', 'US'),
('126', 'GS1 US - Not used', 'US'),
('127', 'GS1 US - Not used', 'US'),
('128', 'GS1 US - Not used', 'US'),
('129', 'GS1 US - Not used', 'US'),
('130', 'GS1 US - Not used', 'US'),
('131', 'GS1 US - Not used', 'US'),
('132', 'GS1 US - Not used', 'US'),
('133', 'GS1 US - Not used', 'US'),
('134', 'GS1 US - Not used', 'US'),
('135', 'GS1 US - Not used', 'US'),
('136', 'GS1 US - Not used', 'US'),
('137', 'GS1 US - Not used', 'US'),
('138', 'GS1 US - Not used', 'US'),
('139', 'GS1 US - Not used', 'US'),
('140', 'Reserved for future use', ''),
('141', 'Reserved for future use', ''),
('142', 'Reserved for future use', ''),
('143', 'Reserved for future use', ''),
('144', 'Reserved for future use', ''),
('145', 'Reserved for future use', ''),
('146', 'Reserved for future use', ''),
('147', 'Reserved for future use', ''),
('148', 'Reserved for future use', ''),
('149', 'Reserved for future use', ''),
('150', 'Reserved for future use', ''),
('151', 'Reserved for future use', ''),
('152', 'Reserved for future use', ''),
('153', 'Reserved for future use', ''),
('154', 'Reserved for future use', ''),
('155', 'Reserved for future use', ''),
('156', 'Reserved for future use', ''),
('157', 'Reserved for future use', ''),
('158', 'Reserved for future use', ''),
('159', 'Reserved for future use', ''),
('160', 'Reserved for future use', ''),
('161', 'Reserved for future use', ''),
('162', 'Reserved for future use', ''),
('163', 'Reserved for future use', ''),
('164', 'Reserved for future use', ''),
('165', 'Reserved for future use', ''),
('166', 'Reserved for future use', ''),
('167', 'Reserved for future use', ''),
('168', 'Reserved for future use', ''),
('169', 'Reserved for future use', ''),
('170', 'Reserved for future use', ''),
('171', 'Reserved for future use', ''),
('172', 'Reserved for future use', ''),
('173', 'Reserved for future use', ''),
('174', 'Reserved for future use', ''),
('175', 'Reserved for future use', ''),
('176', 'Reserved for future use', ''),
('177', 'Reserved for future use', ''),
('178', 'Reserved for future use', ''),
('179', 'Reserved for future use', ''),
('180', 'Reserved for future use', ''),
('181', 'Reserved for future use', ''),
('182', 'Reserved for future use', ''),
('183', 'Reserved for future use', ''),
('184', 'Reserved for future use', ''),
('185', 'Reserved for future use', ''),
('186', 'Reserved for future use', ''),
('187', 'Reserved for future use', ''),
('188', 'Reserved for future use', ''),
('189', 'Reserved for future use', ''),
('190', 'Reserved for future use', ''),
('191', 'Reserved for future use', ''),
('192', 'Reserved for future use', ''),
('193', 'Reserved for future use', ''),
('194', 'Reserved for future use', ''),
('195', 'Reserved for future use', ''),
('196', 'Reserved for future use', ''),
('197', 'Reserved for future use', ''),
('198', 'Reserved for future use', ''),
('199', 'Reserved for future use', ''),
('200', 'Restricted distribution (MO defined)', ''),
('201', 'Restricted distribution (MO defined)', ''),
('202', 'Restricted distribution (MO defined)', ''),
('203', 'Restricted distribution (MO defined)', ''),
('204', 'Restricted distribution (MO defined)', ''),
('205', 'Restricted distribution (MO defined)', ''),
('206', 'Restricted distribution (MO defined)', ''),
('207', 'Restricted distribution (MO defined)', ''),
('208', 'Restricted distribution (MO defined)', ''),
('209', 'Restricted distribution (MO defined)', ''),
('210', 'Restricted distribution (MO defined)', ''),
('211', 'Restricted distribution (MO defined)', ''),
('212', 'Restricted distribution (MO defined)', ''),
('213', 'Restricted distribution (MO defined)', ''),
('214', 'Restricted distribution (MO defined)', ''),
('215', 'Restricted distribution (MO defined)', ''),
('216', 'Restricted distribution (MO defined)', ''),
('217', 'Restricted distribution (MO defined)', ''),
('218', 'Restricted distribution (MO defined)', ''),
('219', 'Restricted distribution (MO defined)', ''),
('220', 'Restricted distribution (MO defined)', ''),
('221', 'Restricted distribution (MO defined)', ''),
('222', 'Restricted distribution (MO defined)', ''),
('223', 'Restricted distribution (MO defined)', ''),
('224', 'Restricted distribution (MO defined)', ''),
('225', 'Restricted distribution (MO defined)', ''),
('226', 'Restricted distribution (MO defined)', ''),
('227', 'Restricted distribution (MO defined)', ''),
('228', 'Restricted distribution (MO defined)', ''),
('229', 'Restricted distribution (MO defined)', ''),
('230', 'Restricted distribution (MO defined)', ''),
('231', 'Restricted distribution (MO defined)', ''),
('232', 'Restricted distribution (MO defined)', ''),
('233', 'Restricted distribution (MO defined)', ''),
('234', 'Restricted distribution (MO defined)', ''),
('235', 'Restricted distribution (MO defined)', ''),
('236', 'Restricted distribution (MO defined)', ''),
('237', 'Restricted distribution (MO defined)', ''),
('238', 'Restricted distribution (MO defined)', ''),
('239', 'Restricted distribution (MO defined)', ''),
('240', 'Restricted distribution (MO defined)', ''),
('241', 'Restricted distribution (MO defined)', ''),
('242', 'Restricted distribution (MO defined)', ''),
('243', 'Restricted distribution (MO defined)', ''),
('244', 'Restricted distribution (MO defined)', ''),
('245', 'Restricted distribution (MO defined)', ''),
('246', 'Restricted distribution (MO defined)', ''),
('247', 'Restricted distribution (MO defined)', ''),
('248', 'Restricted distribution (MO defined)', ''),
('249', 'Restricted distribution (MO defined)', ''),
('250', 'Restricted distribution (MO defined)', ''),
('251', 'Restricted distribution (MO defined)', ''),
('252', 'Restricted distribution (MO defined)', ''),
('253', 'Restricted distribution (MO defined)', ''),
('254', 'Restricted distribution (MO defined)', ''),
('255', 'Restricted distribution (MO defined)', ''),
('256', 'Restricted distribution (MO defined)', ''),
('257', 'Restricted distribution (MO defined)', ''),
('258', 'Restricted distribution (MO defined)', ''),
('259', 'Restricted distribution (MO defined)', ''),
('260', 'Restricted distribution (MO defined)', ''),
('261', 'Restricted distribution (MO defined)', ''),
('262', 'Restricted distribution (MO defined)', ''),
('263', 'Restricted distribution (MO defined)', ''),
('264', 'Restricted distribution (MO defined)', ''),
('265', 'Restricted distribution (MO defined)', ''),
('266', 'Restricted distribution (MO defined)', ''),
('267', 'Restricted distribution (MO defined)', ''),
('268', 'Restricted distribution (MO defined)', ''),
('269', 'Restricted distribution (MO defined)', ''),
('270', 'Restricted distribution (MO defined)', ''),
('271', 'Restricted distribution (MO defined)', ''),
('272', 'Restricted distribution (MO defined)', ''),
('273', 'Restricted distribution (MO defined)', ''),
('274', 'Restricted distribution (MO defined)', ''),
('275', 'Restricted distribution (MO defined)', ''),
('276', 'Restricted distribution (MO defined)', ''),
('277', 'Restricted distribution (MO defined)', ''),
('278', 'Restricted distribution (MO defined)', ''),
('279', 'Restricted distribution (MO defined)', ''),
('280', 'Restricted distribution (MO defined)', ''),
('281', 'Restricted distribution (MO defined)', ''),
('282', 'Restricted distribution (MO defined)', ''),
('283', 'Restricted distribution (MO defined)', ''),
('284', 'Restricted distribution (MO defined)', ''),
('285', 'Restricted distribution (MO defined)', ''),
('286', 'Restricted distribution (MO defined)', ''),
('287', 'Restricted distribution (MO defined)', ''),
('288', 'Restricted distribution (MO defined)', ''),
('289', 'Restricted distribution (MO defined)', ''),
('290', 'Restricted distribution (MO defined)', ''),
('291', 'Restricted distribution (MO defined)', ''),
('292', 'Restricted distribution (MO defined)', ''),
('293', 'Restricted distribution (MO defined)', ''),
('294', 'Restricted distribution (MO defined)', ''),
('295', 'Restricted distribution (MO defined)', ''),
('296', 'Restricted distribution (MO defined)', ''),
('297', 'Restricted distribution (MO defined)', ''),
('298', 'Restricted distribution (MO defined)', ''),
('299', 'Restricted distribution (MO defined)', ''),
('300', 'GS1 France', 'FR'),
('301', 'GS1 France', 'FR'),
('302', 'GS1 France', 'FR'),
('303', 'GS1 France', 'FR'),
('304', 'GS1 France', 'FR'),
('305', 'GS1 France', 'FR'),
('306', 'GS1 France', 'FR'),
('307', 'GS1 France', 'FR'),
('308', 'GS1 France', 'FR'),
('309', 'GS1 France', 'FR'),
('310', 'GS1 France', 'FR'),
('311', 'GS1 France', 'FR'),
('312', 'GS1 France', 'FR'),
('313', 'GS1 France', 'FR'),
('314', 'GS1 France', 'FR'),
('315', 'GS1 France', 'FR'),
('316', 'GS1 France', 'FR'),
('317', 'GS1 France', 'FR'),
('318', 'GS1 France', 'FR'),
('319', 'GS1 France', 'FR'),
('320', 'GS1 France', 'FR'),
('321', 'GS1 France', 'FR'),
('322', 'GS1 France', 'FR'),
('323', 'GS1 France', 'FR'),
('324', 'GS1 France', 'FR'),
('325', 'GS1 France', 'FR'),
('326', 'GS1 France', 'FR'),
('327', 'GS1 France', 'FR'),
('328', 'GS1 France', 'FR'),
('329', 'GS1 France', 'FR'),
('330', 'GS1 France', 'FR'),
('331', 'GS1 France', 'FR'),
('332', 'GS1 France', 'FR'),
('333', 'GS1 France', 'FR'),
('334', 'GS1 France', 'FR'),
('335', 'GS1 France', 'FR'),
('336', 'GS1 France', 'FR'),
('337', 'GS1 France', 'FR'),
('338', 'GS1 France', 'FR'),
('339', 'GS1 France', 'FR'),
('340', 'GS1 France', 'FR'),
('341', 'GS1 France', 'FR'),
('342', 'GS1 France', 'FR'),
('343', 'GS1 France', 'FR'),
('344', 'GS1 France', 'FR'),
('345', 'GS1 France', 'FR'),
('346', 'GS1 France', 'FR'),
('347', 'GS1 France', 'FR'),
('348', 'GS1 France', 'FR'),
('349', 'GS1 France', 'FR'),
('350', 'GS1 France', 'FR'),
('351', 'GS1 France', 'FR'),
('352', 'GS1 France', 'FR'),
('353', 'GS1 France', 'FR'),
('354', 'GS1 France', 'FR'),
('355', 'GS1 France', 'FR'),
('356', 'GS1 France', 'FR'),
('357', 'GS1 France', 'FR'),
('358', 'GS1 France', 'FR'),
('359', 'GS1 France', 'FR'),
('360', 'GS1 France', 'FR'),
('361', 'GS1 France', 'FR'),
('362', 'GS1 France', 'FR'),
('363', 'GS1 France', 'FR'),
('364', 'GS1 France', 'FR'),
('365', 'GS1 France', 'FR'),
('366', 'GS1 France', 'FR'),
('367', 'GS1 France', 'FR'),
('368', 'GS1 France', 'FR'),
('369', 'GS1 France', 'FR'),
('370', 'GS1 France', 'FR'),
('371', 'GS1 France', 'FR'),
('372', 'GS1 France', 'FR'),
('373', 'GS1 France', 'FR'),
('374', 'GS1 France', 'FR'),
('375', 'GS1 France', 'FR'),
('376', 'GS1 France', 'FR'),
('377', 'GS1 France', 'FR'),
('378', 'GS1 France', 'FR'),
('379', 'GS1 France', 'FR'),
('380', 'GS1 Bulgaria', 'BG'),
('381', 'Reserved for future use  ', ''),
('382', 'Reserved for future use  ', ''),
('383', 'GS1 Slovenija', 'SI'),
('384', 'Reserved for future use  ', ''),
('385', 'GS1 Croatia', 'HR'),
('386', 'Reserved for future use  ', ''),
('387', 'GS1 BIH (Bosnia-Herzegovina)', 'BA'),
('388', 'Reserved for future use  ', ''),
('389', 'GS1 Montenegro', 'ME'),
('390', 'Reserved for future use  ', ''),
('391', 'Reserved for future use  ', ''),
('392', 'Reserved for future use  ', ''),
('393', 'Reserved for future use  ', ''),
('394', 'Reserved for future use  ', ''),
('395', 'Reserved for future use  ', ''),
('396', 'Reserved for future use  ', ''),
('397', 'Reserved for future use  ', ''),
('398', 'Reserved for future use  ', ''),
('399', 'Reserved for future use  ', ''),
('400', 'GS1 Germany', 'DE'),
('401', 'GS1 Germany', 'DE'),
('402', 'GS1 Germany', 'DE'),
('403', 'GS1 Germany', 'DE'),
('404', 'GS1 Germany', 'DE'),
('405', 'GS1 Germany', 'DE'),
('406', 'GS1 Germany', 'DE'),
('407', 'GS1 Germany', 'DE'),
('408', 'GS1 Germany', 'DE'),
('409', 'GS1 Germany', 'DE'),
('410', 'GS1 Germany', 'DE'),
('411', 'GS1 Germany', 'DE'),
('412', 'GS1 Germany', 'DE'),
('413', 'GS1 Germany', 'DE'),
('414', 'GS1 Germany', 'DE'),
('415', 'GS1 Germany', 'DE'),
('416', 'GS1 Germany', 'DE'),
('417', 'GS1 Germany', 'DE'),
('418', 'GS1 Germany', 'DE'),
('419', 'GS1 Germany', 'DE'),
('420', 'GS1 Germany', 'DE'),
('421', 'GS1 Germany', 'DE'),
('422', 'GS1 Germany', 'DE'),
('423', 'GS1 Germany', 'DE'),
('424', 'GS1 Germany', 'DE'),
('425', 'GS1 Germany', 'DE'),
('426', 'GS1 Germany', 'DE'),
('427', 'GS1 Germany', 'DE'),
('428', 'GS1 Germany', 'DE'),
('429', 'GS1 Germany', 'DE'),
('430', 'GS1 Germany', 'DE'),
('431', 'GS1 Germany', 'DE'),
('432', 'GS1 Germany', 'DE'),
('433', 'GS1 Germany', 'DE'),
('434', 'GS1 Germany', 'DE'),
('435', 'GS1 Germany', 'DE'),
('436', 'GS1 Germany', 'DE'),
('437', 'GS1 Germany', 'DE'),
('438', 'GS1 Germany', 'DE'),
('439', 'GS1 Germany', 'DE'),
('440', 'GS1 Germany', 'DE'),
('441', 'Reserved for future use  ', ''),
('442', 'Reserved for future use  ', ''),
('443', 'Reserved for future use  ', ''),
('444', 'Reserved for future use  ', ''),
('445', 'Reserved for future use  ', ''),
('446', 'Reserved for future use  ', ''),
('447', 'Reserved for future use  ', ''),
('448', 'Reserved for future use  ', ''),
('449', 'Reserved for future use  ', ''),
('450', 'GS1 Japan', 'JP'),
('451', 'GS1 Japan', 'JP'),
('452', 'GS1 Japan', 'JP'),
('453', 'GS1 Japan', 'JP'),
('454', 'GS1 Japan', 'JP'),
('455', 'GS1 Japan', 'JP'),
('456', 'GS1 Japan', 'JP'),
('457', 'GS1 Japan', 'JP'),
('458', 'GS1 Japan', 'JP'),
('459', 'GS1 Japan', 'JP'),
('460', 'GS1 Russia', 'RU'),
('461', 'GS1 Russia', 'RU'),
('462', 'GS1 Russia', 'RU'),
('463', 'GS1 Russia', 'RU'),
('464', 'GS1 Russia', 'RU'),
('465', 'GS1 Russia', 'RU'),
('466', 'GS1 Russia', 'RU'),
('467', 'GS1 Russia', 'RU'),
('468', 'GS1 Russia', 'RU'),
('469', 'GS1 Russia', 'RU'),
('470', 'GS1 Kyrgyzstan', 'KG'),
('471', 'GS1 Taiwan', 'TW'),
('472', 'Reserved for future use  ', ''),
('473', 'Reserved for future use  ', ''),
('474', 'GS1 Estonia', 'EE'),
('475', 'GS1 Latvia', 'LV'),
('476', 'GS1 Azerbaijan', 'AZ'),
('477', 'GS1 Lithuania', 'LT'),
('478', 'GS1 Uzbekistan', 'UZ'),
('479', 'GS1 Sri Lanka', 'LK'),
('480', 'GS1 Philippines', 'PH'),
('481', 'GS1 Belarus', 'BY'),
('482', 'GS1 Ukraine', 'UA'),
('483', 'Reserved for future use  ', ''),
('484', 'GS1 Moldova', 'MD'),
('485', 'GS1 Armenia', 'AM'),
('486', 'GS1 Georgia', 'GE'),
('487', 'GS1 Kazakstan', 'KZ'),
('488', 'GS1 Tajikistan', 'TJ'),
('489', 'GS1 Hong Kong', 'HK'),
('490', 'GS1 Japan', 'JP'),
('491', 'GS1 Japan', 'JP'),
('492', 'GS1 Japan', 'JP'),
('493', 'GS1 Japan', 'JP'),
('494', 'GS1 Japan', 'JP'),
('495', 'GS1 Japan', 'JP'),
('496', 'GS1 Japan', 'JP'),
('497', 'GS1 Japan', 'JP'),
('498', 'GS1 Japan', 'JP'),
('499', 'GS1 Japan', 'JP'),
('500', 'GS1 UK', 'GB'),
('501', 'GS1 UK', 'GB'),
('502', 'GS1 UK', 'GB'),
('503', 'GS1 UK', 'GB'),
('504', 'GS1 UK', 'GB'),
('505', 'GS1 UK', 'GB'),
('506', 'GS1 UK', 'GB'),
('507', 'GS1 UK', 'GB'),
('508', 'GS1 UK', 'GB'),
('509', 'GS1 UK', 'GB'),
('510', 'Reserved for future use  ', ''),
('511', 'Reserved for future use  ', ''),
('512', 'Reserved for future use  ', ''),
('513', 'Reserved for future use  ', ''),
('514', 'Reserved for future use  ', ''),
('515', 'Reserved for future use  ', ''),
('516', 'Reserved for future use  ', ''),
('517', 'Reserved for future use  ', ''),
('518', 'Reserved for future use  ', ''),
('519', 'Reserved for future use  ', ''),
('520', 'GS1 Association Greece', 'GR'),
('521', 'GS1 Association Greece', 'GR'),
('522', 'Reserved for future use  ', ''),
('523', 'Reserved for future use  ', ''),
('524', 'Reserved for future use  ', ''),
('525', 'Reserved for future use  ', ''),
('526', 'Reserved for future use  ', ''),
('527', 'Reserved for future use  ', ''),
('528', 'GS1 Lebanon', 'LB'),
('529', 'GS1 Cyprus', 'CY'),
('530', 'GS1 Albania', 'AL'),
('531', 'GS1 MAC (FYR Macedonia)', 'MK'),
('532', 'Reserved for future use  ', ''),
('533', 'Reserved for future use  ', ''),
('534', 'Reserved for future use  ', ''),
('535', 'GS1 Malta', 'MT'),
('536', 'Reserved for future use  ', ''),
('537', 'Reserved for future use  ', ''),
('538', 'Reserved for future use  ', ''),
('539', 'GS1 Ireland', 'IE'),
('540', 'GS1 Belgium & Luxembourg', 'BE'),
('541', 'GS1 Belgium & Luxembourg', 'BE'),
('542', 'GS1 Belgium & Luxembourg', 'BE'),
('543', 'GS1 Belgium & Luxembourg', 'BE'),
('544', 'GS1 Belgium & Luxembourg', 'BE'),
('545', 'GS1 Belgium & Luxembourg', 'BE'),
('546', 'GS1 Belgium & Luxembourg', 'BE'),
('547', 'GS1 Belgium & Luxembourg', 'BE'),
('548', 'GS1 Belgium & Luxembourg', 'BE'),
('549', 'GS1 Belgium & Luxembourg', 'BE'),
('550', 'Reserved for future use  ', ''),
('551', 'Reserved for future use  ', ''),
('552', 'Reserved for future use  ', ''),
('553', 'Reserved for future use  ', ''),
('554', 'Reserved for future use  ', ''),
('555', 'Reserved for future use  ', ''),
('556', 'Reserved for future use  ', ''),
('557', 'Reserved for future use  ', ''),
('558', 'Reserved for future use  ', ''),
('559', 'Reserved for future use  ', ''),
('560', 'GS1 Portugal', 'PT'),
('561', 'Reserved for future use  ', ''),
('562', 'Reserved for future use  ', ''),
('563', 'Reserved for future use  ', ''),
('564', 'Reserved for future use  ', ''),
('565', 'Reserved for future use  ', ''),
('566', 'Reserved for future use  ', ''),
('567', 'Reserved for future use  ', ''),
('568', 'Reserved for future use  ', ''),
('569', 'GS1 Iceland', 'IS'),
('570', 'GS1 Denmark', 'DK'),
('571', 'GS1 Denmark', 'DK'),
('572', 'GS1 Denmark', 'DK'),
('573', 'GS1 Denmark', 'DK'),
('574', 'GS1 Denmark', 'DK'),
('575', 'GS1 Denmark', 'DK'),
('576', 'GS1 Denmark', 'DK'),
('577', 'GS1 Denmark', 'DK'),
('578', 'GS1 Denmark', 'DK'),
('579', 'GS1 Denmark', 'DK'),
('580', 'Reserved for future use  ', ''),
('581', 'Reserved for future use  ', ''),
('582', 'Reserved for future use  ', ''),
('583', 'Reserved for future use  ', ''),
('584', 'Reserved for future use  ', ''),
('585', 'Reserved for future use  ', ''),
('586', 'Reserved for future use  ', ''),
('587', 'Reserved for future use  ', ''),
('588', 'Reserved for future use  ', ''),
('589', 'Reserved for future use  ', ''),
('590', 'GS1 Poland', 'PL'),
('591', 'Reserved for future use  ', ''),
('592', 'Reserved for future use  ', ''),
('593', 'Reserved for future use  ', ''),
('594', 'GS1 Romania', 'RO'),
('595', 'Reserved for future use  ', ''),
('596', 'Reserved for future use  ', ''),
('597', 'Reserved for future use  ', ''),
('598', 'Reserved for future use  ', ''),
('599', 'GS1 Hungary', 'HU'),
('600', 'GS1 South Africa', 'ZA'),
('601', 'GS1 South Africa', 'ZA'),
('602', 'Reserved for future use  ', ''),
('603', 'GS1 Ghana', 'GH'),
('604', 'GS1 Senegal', 'SN'),
('605', 'Reserved for future use  ', ''),
('606', 'Reserved for future use  ', ''),
('607', 'Reserved for future use  ', ''),
('608', 'GS1 Bahrain', 'BH'),
('609', 'GS1 Mauritius', 'MR'),
('610', 'Reserved for future use  ', ''),
('611', 'GS1 Morocco', 'MA'),
('612', 'Reserved for future use  ', ''),
('613', 'GS1 Algeria', 'DZ'),
('614', 'Reserved for future use  ', ''),
('615', 'GS1 Nigeria', 'NG'),
('616', 'GS1 Kenya', 'KE'),
('617', 'Reserved for future use  ', ''),
('618', 'GS1 Ivory Coast', 'CI'),
('619', 'GS1 Tunisia', 'TN'),
('620', 'GS1 Tanzania', 'TZ'),
('621', 'GS1 Syria', 'SY'),
('622', 'GS1 Egypt', 'EG'),
('623', 'GS1 Brunei', 'BN'),
('624', 'GS1 Libya', 'LY'),
('625', 'GS1 Jordan', 'JO'),
('626', 'GS1 Iran', 'IR'),
('627', 'GS1 Kuwait', 'KW'),
('628', 'GS1 Saudi Arabia', 'SA'),
('629', 'GS1 Emirates', 'AE'),
('630', 'Reserved for future use  ', ''),
('631', 'Reserved for future use  ', ''),
('632', 'Reserved for future use  ', ''),
('633', 'Reserved for future use  ', ''),
('634', 'Reserved for future use  ', ''),
('635', 'Reserved for future use  ', ''),
('636', 'Reserved for future use  ', ''),
('637', 'Reserved for future use  ', ''),
('638', 'Reserved for future use  ', ''),
('639', 'Reserved for future use  ', ''),
('640', 'GS1 Finland', 'FI'),
('641', 'GS1 Finland', 'FI'),
('642', 'GS1 Finland', 'FI'),
('643', 'GS1 Finland', 'FI'),
('644', 'GS1 Finland', 'FI'),
('645', 'GS1 Finland', 'FI'),
('646', 'GS1 Finland', 'FI'),
('647', 'GS1 Finland', 'FI'),
('648', 'GS1 Finland', 'FI'),
('649', 'GS1 Finland', 'FI'),
('650', 'Reserved for future use  ', ''),
('651', 'Reserved for future use  ', ''),
('652', 'Reserved for future use  ', ''),
('653', 'Reserved for future use  ', ''),
('654', 'Reserved for future use  ', ''),
('655', 'Reserved for future use  ', ''),
('656', 'Reserved for future use  ', ''),
('657', 'Reserved for future use  ', ''),
('658', 'Reserved for future use  ', ''),
('659', 'Reserved for future use  ', ''),
('660', 'Reserved for future use  ', ''),
('661', 'Reserved for future use  ', ''),
('662', 'Reserved for future use  ', ''),
('663', 'Reserved for future use  ', ''),
('664', 'Reserved for future use  ', ''),
('665', 'Reserved for future use  ', ''),
('666', 'Reserved for future use  ', ''),
('667', 'Reserved for future use  ', ''),
('668', 'Reserved for future use  ', ''),
('669', 'Reserved for future use  ', ''),
('670', 'Reserved for future use  ', ''),
('671', 'Reserved for future use  ', ''),
('672', 'Reserved for future use  ', ''),
('673', 'Reserved for future use  ', ''),
('674', 'Reserved for future use  ', ''),
('675', 'Reserved for future use  ', ''),
('676', 'Reserved for future use  ', ''),
('677', 'Reserved for future use  ', ''),
('678', 'Reserved for future use  ', ''),
('679', 'Reserved for future use  ', ''),
('680', 'Reserved for future use  ', ''),
('681', 'Reserved for future use  ', ''),
('682', 'Reserved for future use  ', ''),
('683', 'Reserved for future use  ', ''),
('684', 'Reserved for future use  ', ''),
('685', 'Reserved for future use  ', ''),
('686', 'Reserved for future use  ', ''),
('687', 'Reserved for future use  ', ''),
('688', 'Reserved for future use  ', ''),
('689', 'Reserved for future use  ', ''),
('690', 'GS1 China', 'CN'),
('691', 'GS1 China', 'CN'),
('692', 'GS1 China', 'CN'),
('693', 'GS1 China', 'CN'),
('694', 'GS1 China', 'CN'),
('695', 'GS1 China', 'CN'),
('696', 'Reserved for future use  ', ''),
('697', 'Reserved for future use  ', ''),
('698', 'Reserved for future use  ', ''),
('699', 'Reserved for future use  ', ''),
('700', 'GS1 Norway', 'NO'),
('701', 'GS1 Norway', 'NO'),
('702', 'GS1 Norway', 'NO'),
('703', 'GS1 Norway', 'NO'),
('704', 'GS1 Norway', 'NO'),
('705', 'GS1 Norway', 'NO'),
('706', 'GS1 Norway', 'NO'),
('707', 'GS1 Norway', 'NO'),
('708', 'GS1 Norway', 'NO'),
('709', 'GS1 Norway', 'NO'),
('710', 'Reserved for future use  ', ''),
('711', 'Reserved for future use  ', ''),
('712', 'Reserved for future use  ', ''),
('713', 'Reserved for future use  ', ''),
('714', 'Reserved for future use  ', ''),
('715', 'Reserved for future use  ', ''),
('716', 'Reserved for future use  ', ''),
('717', 'Reserved for future use  ', ''),
('718', 'Reserved for future use  ', ''),
('719', 'Reserved for future use  ', ''),
('720', 'Reserved for future use  ', ''),
('721', 'Reserved for future use  ', ''),
('722', 'Reserved for future use  ', ''),
('723', 'Reserved for future use  ', ''),
('724', 'Reserved for future use  ', ''),
('725', 'Reserved for future use  ', ''),
('726', 'Reserved for future use  ', ''),
('727', 'Reserved for future use  ', ''),
('728', 'Reserved for future use  ', ''),
('729', 'GS1 Israel', 'IL'),
('730', 'GS1 Sweden', 'SE'),
('731', 'GS1 Sweden', 'SE'),
('732', 'GS1 Sweden', 'SE'),
('733', 'GS1 Sweden', 'SE'),
('734', 'GS1 Sweden', 'SE'),
('735', 'GS1 Sweden', 'SE'),
('736', 'GS1 Sweden', 'SE'),
('737', 'GS1 Sweden', 'SE'),
('738', 'GS1 Sweden', 'SE'),
('739', 'GS1 Sweden', 'SE'),
('740', 'GS1 Guatemala', 'GT'),
('741', 'GS1 El Salvador', 'SV'),
('742', 'GS1 Honduras', 'HN'),
('743', 'GS1 Nicaragua', 'NI'),
('744', 'GS1 Costa Rica', 'CR'),
('745', 'GS1 Panama', 'PA'),
('746', 'GS1 Republica Dominicana', 'DO'),
('747', 'Reserved for future use  ', ''),
('748', 'Reserved for future use  ', ''),
('749', 'Reserved for future use  ', ''),
('750', 'GS1 Mexico', 'MX'),
('751', 'Reserved for future use  ', ''),
('752', 'Reserved for future use  ', ''),
('753', 'Reserved for future use  ', ''),
('754', 'GS1 Canada', 'CA'),
('755', 'GS1 Canada', 'CA'),
('756', 'Reserved for future use  ', ''),
('757', 'Reserved for future use  ', ''),
('758', 'Reserved for future use  ', ''),
('759', 'GS1 Venezuela', 'VE'),
('760', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('761', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('762', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('763', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('764', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('765', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('766', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('767', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('768', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('769', 'GS1 Schweiz, Suisse, Svizzera', 'CH'),
('770', 'GS1 Colombia', 'CO'),
('771', 'GS1 Colombia', 'CO'),
('772', 'Reserved for future use  ', ''),
('773', 'GS1 Uruguay', 'UY'),
('774', 'Reserved for future use  ', ''),
('775', 'GS1 Peru', 'PE'),
('776', 'Reserved for future use  ', ''),
('777', 'GS1 Bolivia', 'BO'),
('778', 'GS1 Argentina', 'AR'),
('779', 'GS1 Argentina', 'AR'),
('780', 'GS1 Chile', 'CL'),
('781', 'Reserved for future use  ', ''),
('782', 'Reserved for future use  ', ''),
('783', 'Reserved for future use  ', ''),
('784', 'GS1 Paraguay', 'PY'),
('785', 'Reserved for future use  ', ''),
('786', 'GS1 Ecuador', 'EC'),
('787', 'Reserved for future use  ', ''),
('788', 'Reserved for future use  ', ''),
('789', 'GS1 Brasil  ', 'BR'),
('790', 'GS1 Brasil  ', 'BR'),
('791', 'Reserved for future use  ', ''),
('792', 'Reserved for future use  ', ''),
('793', 'Reserved for future use  ', ''),
('794', 'Reserved for future use  ', ''),
('795', 'Reserved for future use  ', ''),
('796', 'Reserved for future use  ', ''),
('797', 'Reserved for future use  ', ''),
('798', 'Reserved for future use  ', ''),
('799', 'Reserved for future use  ', ''),
('800', 'GS1 Italy  ', 'IT'),
('801', 'GS1 Italy  ', 'IT'),
('802', 'GS1 Italy  ', 'IT'),
('803', 'GS1 Italy  ', 'IT'),
('804', 'GS1 Italy  ', 'IT'),
('805', 'GS1 Italy  ', 'IT'),
('806', 'GS1 Italy  ', 'IT'),
('807', 'GS1 Italy  ', 'IT'),
('808', 'GS1 Italy  ', 'IT'),
('809', 'GS1 Italy  ', 'IT'),
('810', 'GS1 Italy  ', 'IT'),
('811', 'GS1 Italy  ', 'IT'),
('812', 'GS1 Italy  ', 'IT'),
('813', 'GS1 Italy  ', 'IT'),
('814', 'GS1 Italy  ', 'IT'),
('815', 'GS1 Italy  ', 'IT'),
('816', 'GS1 Italy  ', 'IT'),
('817', 'GS1 Italy  ', 'IT'),
('818', 'GS1 Italy  ', 'IT'),
('819', 'GS1 Italy  ', 'IT'),
('820', 'GS1 Italy  ', 'IT'),
('821', 'GS1 Italy  ', 'IT'),
('822', 'GS1 Italy  ', 'IT'),
('823', 'GS1 Italy  ', 'IT'),
('824', 'GS1 Italy  ', 'IT'),
('825', 'GS1 Italy  ', 'IT'),
('826', 'GS1 Italy  ', 'IT'),
('827', 'GS1 Italy  ', 'IT'),
('828', 'GS1 Italy  ', 'IT'),
('829', 'GS1 Italy  ', 'IT'),
('830', 'GS1 Italy  ', 'IT'),
('831', 'GS1 Italy  ', 'IT'),
('832', 'GS1 Italy  ', 'IT'),
('833', 'GS1 Italy  ', 'IT'),
('834', 'GS1 Italy  ', 'IT'),
('835', 'GS1 Italy  ', 'IT'),
('836', 'GS1 Italy  ', 'IT'),
('837', 'GS1 Italy  ', 'IT'),
('838', 'GS1 Italy  ', 'IT'),
('839', 'GS1 Italy  ', 'IT'),
('840', 'GS1 Spain  ', 'ES'),
('841', 'GS1 Spain  ', 'ES'),
('842', 'GS1 Spain  ', 'ES'),
('843', 'GS1 Spain  ', 'ES'),
('844', 'GS1 Spain  ', 'ES'),
('845', 'GS1 Spain  ', 'ES'),
('846', 'GS1 Spain  ', 'ES'),
('847', 'GS1 Spain  ', 'ES'),
('848', 'GS1 Spain  ', 'ES'),
('849', 'GS1 Spain  ', 'ES'),
('850', 'GS1 Cuba', 'CU'),
('851', 'Reserved for future use  ', ''),
('852', 'Reserved for future use  ', ''),
('853', 'Reserved for future use  ', ''),
('854', 'Reserved for future use  ', ''),
('855', 'Reserved for future use  ', ''),
('856', 'Reserved for future use  ', ''),
('857', 'Reserved for future use  ', ''),
('858', 'GS1 Slovakia', 'SK'),
('859', 'GS1 Czech', 'CZ'),
('860', ' GS1 Serbia', 'RS'),
('861', 'Reserved for future use  ', ''),
('862', 'Reserved for future use  ', ''),
('863', 'Reserved for future use  ', ''),
('864', 'Reserved for future use  ', ''),
('865', 'GS1 Mongolia', 'MN'),
('866', 'Reserved for future use  ', ''),
('867', 'GS1 North Korea', 'KP'),
('868', 'GS1 Turkey', 'TR'),
('869', 'GS1 Turkey', 'TR'),
('870', 'GS1 Netherlands', 'NL'),
('871', 'GS1 Netherlands', 'NL'),
('872', 'GS1 Netherlands', 'NL'),
('873', 'GS1 Netherlands', 'NL'),
('874', 'GS1 Netherlands', 'NL'),
('875', 'GS1 Netherlands', 'NL'),
('876', 'GS1 Netherlands', 'NL'),
('877', 'GS1 Netherlands', 'NL'),
('878', 'GS1 Netherlands', 'NL'),
('879', 'GS1 Netherlands', 'NL'),
('880', 'GS1 South Korea', 'KR'),
('881', 'Reserved for future use  ', ''),
('882', 'Reserved for future use  ', ''),
('883', 'Reserved for future use  ', ''),
('884', 'GS1 Cambodia', 'KH'),
('885', 'GS1 Thailand', 'TH'),
('886', 'Reserved for future use  ', ''),
('887', 'Reserved for future use  ', ''),
('888', 'GS1 Singapore', 'SG'),
('889', 'Reserved for future use  ', ''),
('890', 'GS1 India', 'IN'),
('891', 'Reserved for future use  ', ''),
('892', 'Reserved for future use  ', ''),
('893', 'GS1 Vietnam', 'VN'),
('894', 'Reserved for future use  ', ''),
('895', 'Reserved for future use  ', ''),
('896', 'GS1 Pakistan', 'PK'),
('897', 'Reserved for future use  ', ''),
('898', 'Reserved for future use  ', ''),
('899', 'GS1 Indonesia', 'ID'),
('900', 'GS1 Austria', 'AT'),
('901', 'GS1 Austria', 'AT'),
('902', 'GS1 Austria', 'AT'),
('903', 'GS1 Austria', 'AT'),
('904', 'GS1 Austria', 'AT'),
('905', 'GS1 Austria', 'AT'),
('906', 'GS1 Austria', 'AT'),
('907', 'GS1 Austria', 'AT'),
('908', 'GS1 Austria', 'AT'),
('909', 'GS1 Austria', 'AT'),
('910', 'GS1 Austria', 'AT'),
('911', 'GS1 Austria', 'AT'),
('912', 'GS1 Austria', 'AT'),
('913', 'GS1 Austria', 'AT'),
('914', 'GS1 Austria', 'AT'),
('915', 'GS1 Austria', 'AT'),
('916', 'GS1 Austria', 'AT'),
('917', 'GS1 Austria', 'AT'),
('918', 'GS1 Austria', 'AT'),
('919', 'GS1 Austria', 'AT'),
('920', 'Reserved for future use  ', ''),
('921', 'Reserved for future use  ', ''),
('922', 'Reserved for future use  ', ''),
('923', 'Reserved for future use  ', ''),
('924', 'Reserved for future use  ', ''),
('925', 'Reserved for future use  ', ''),
('926', 'Reserved for future use  ', ''),
('927', 'Reserved for future use  ', ''),
('928', 'Reserved for future use  ', ''),
('929', 'Reserved for future use  ', ''),
('930', 'GS1 Australia', 'AU'),
('931', 'GS1 Australia', 'AU'),
('932', 'GS1 Australia', 'AU'),
('933', 'GS1 Australia', 'AU'),
('934', 'GS1 Australia', 'AU'),
('935', 'GS1 Australia', 'AU'),
('936', 'GS1 Australia', 'AU'),
('937', 'GS1 Australia', 'AU'),
('938', 'GS1 Australia', 'AU'),
('939', 'GS1 Australia', 'AU'),
('940', 'GS1 New Zealand', 'NZ'),
('941', 'GS1 New Zealand', 'NZ'),
('942', 'GS1 New Zealand', 'NZ'),
('943', 'GS1 New Zealand', 'NZ'),
('944', 'GS1 New Zealand', 'NZ'),
('945', 'GS1 New Zealand', 'NZ'),
('946', 'GS1 New Zealand', 'NZ'),
('947', 'GS1 New Zealand', 'NZ'),
('948', 'GS1 New Zealand', 'NZ'),
('949', 'GS1 New Zealand', 'NZ'),
('950', 'GS1 Global Office', ''),
('951', 'GS1 Global Office (EPCglobal)', ''),
('952', 'Reserved for future use  ', ''),
('953', 'Reserved for future use  ', ''),
('954', 'Reserved for future use  ', ''),
('955', 'GS1 Malaysia', 'MY'),
('956', 'Reserved for future use  ', ''),
('957', 'Reserved for future use  ', ''),
('958', 'GS1 Macau', 'MO'),
('959', 'Reserved for future use  ', ''),
('960', 'Global Office (GTIN-8s)', ''),
('961', 'Global Office (GTIN-8s)', ''),
('962', 'Global Office (GTIN-8s)', ''),
('963', 'Global Office (GTIN-8s)', ''),
('964', 'Global Office (GTIN-8s)', ''),
('965', 'Global Office (GTIN-8s)', ''),
('966', 'Global Office (GTIN-8s)', ''),
('967', 'Global Office (GTIN-8s)', ''),
('968', 'Global Office (GTIN-8s)', ''),
('969', 'Global Office (GTIN-8s)', ''),
('970', 'Reserved for future use  ', ''),
('971', 'Reserved for future use  ', ''),
('972', 'Reserved for future use  ', ''),
('973', 'Reserved for future use  ', ''),
('974', 'Reserved for future use  ', ''),
('975', 'Reserved for future use  ', ''),
('976', 'Reserved for future use  ', ''),
('977', 'Serial publications (ISSN)', 'WW'),
('978', 'Bookland (ISBN)', 'WW'),
('979', 'Bookland (ISBN)', 'WW'),
('980', 'Refund receipts', ''),
('981', 'Common Currency Coupons', ''),
('982', 'Common Currency Coupons', ''),
('983', 'Common Currency Coupons', ''),
('984', 'Reserved for future use  ', ''),
('985', 'Reserved for future use  ', ''),
('986', 'Reserved for future use  ', ''),
('987', 'Reserved for future use  ', ''),
('988', 'Reserved for future use  ', ''),
('989', 'Reserved for future use  ', ''),
('990', 'Coupons', ''),
('991', 'Coupons', ''),
('992', 'Coupons', ''),
('993', 'Coupons', ''),
('994', 'Coupons', ''),
('995', 'Coupons', ''),
('996', 'Coupons', ''),
('997', 'Coupons', ''),
('998', 'Coupons', ''),
('999', 'Coupons', '');

-- --------------------------------------------------------


