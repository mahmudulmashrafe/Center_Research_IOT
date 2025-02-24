-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Feb 24, 2025 at 04:09 AM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cattle_management_iot_server`
--

-- --------------------------------------------------------

--
-- Table structure for table `distance_data`
--

CREATE TABLE `distance_data` (
  `id` int(11) NOT NULL,
  `distance` float DEFAULT NULL,
  `timestamp` timestamp NOT NULL DEFAULT current_timestamp(),
  `status` tinyint(1) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `distance_data`
--

INSERT INTO `distance_data` (`id`, `distance`, `timestamp`, `status`) VALUES
(1431, 9.74, '2025-02-19 07:32:54', 0),
(1432, 9.76, '2025-02-19 07:33:05', 1),
(1433, 9.76, '2025-02-19 07:33:16', 1),
(1434, 9.74, '2025-02-19 07:33:27', 1),
(1435, 9.76, '2025-02-19 07:33:40', 1),
(1436, 9.76, '2025-02-19 07:33:53', 1),
(1437, 9.76, '2025-02-19 07:34:01', 1),
(1438, 9.76, '2025-02-19 07:34:11', 1),
(1439, 9.76, '2025-02-19 07:34:21', 1),
(1440, 9.76, '2025-02-19 07:34:33', 1),
(1441, 9.76, '2025-02-19 07:34:43', 1),
(1442, 3198.38, '2025-02-19 07:34:54', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `distance_data`
--
ALTER TABLE `distance_data`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `distance_data`
--
ALTER TABLE `distance_data`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1443;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
