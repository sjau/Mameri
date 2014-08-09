-- phpMyAdmin SQL Dump
-- version 3.4.9
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Aug 09, 2014 at 02:16 PM
-- Server version: 5.5.38
-- PHP Version: 5.5.9-1ubuntu4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `mameri`
--

-- --------------------------------------------------------

--
-- Table structure for table `roles`
--

CREATE TABLE IF NOT EXISTS `roles` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `projectOwner` enum('No','Yes') COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT 'No',
  `projectBilling` enum('No','Yes') COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT 'No',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci AUTO_INCREMENT=2 ;

--
-- Dumping data for table `roles`
--

INSERT INTO `roles` (`id`, `name`, `projectOwner`, `projectBilling`) VALUES
(1, 'Admin', 'No', 'No');

-- --------------------------------------------------------

--
-- Table structure for table `userPrefs`
--

CREATE TABLE IF NOT EXISTS `userPrefs` (
  `id` int(11) NOT NULL,
  `name` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `initials` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `vatNumber` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `vatID` int(5) NOT NULL,
  `currency` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ownBankDetails` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `ownBankAccount` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `ownBankAccountIBAN` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `escrowBankDetails` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `escrowBankAccount` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `escrowBankIBAN` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `phoneDirect` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `phoneMobile` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `faxDirect` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `signature` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `rateHour` decimal(10,2) NOT NULL,
  `rateCopy` decimal(6,2) NOT NULL,
  `rateMileage` decimal(6,2) NOT NULL,
  `smallExpensesFlatrate` decimal(4,2) NOT NULL,
  `logMinimal` decimal(6,2) NOT NULL,
  `logPrecision` decimal(6,2) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `FK_vatID` (`vatID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(12) NOT NULL AUTO_INCREMENT,
  `login` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `role` int(5) NOT NULL,
  `enabled` tinyint(1) NOT NULL DEFAULT '1',
  `salt` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `login` (`login`),
  KEY `FK_role` (`role`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `vat`
--

CREATE TABLE IF NOT EXISTS `vat` (
  `id` int(5) NOT NULL AUTO_INCREMENT,
  `vat` decimal(4,2) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `vat` (`vat`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci AUTO_INCREMENT=3 ;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `userPrefs`
--
ALTER TABLE `userPrefs`
  ADD CONSTRAINT `FK_id` FOREIGN KEY (`id`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_vatID` FOREIGN KEY (`vatID`) REFERENCES `vat` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `FK_role` FOREIGN KEY (`role`) REFERENCES `roles` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
