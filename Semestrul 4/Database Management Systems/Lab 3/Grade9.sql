USE Test

INSERT INTO RestaurantChain ( RestaurantName, Adress, Phone, MichelinStars)
VALUES ( 'Sample Restaurant', '123 Main St', '555-5555', 3);


-- Dirty Reads: Transaction 2
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
BEGIN TRANSACTION;
SELECT * FROM RestaurantChain WHERE RestaurantID = 1;
WAITFOR DELAY '00:00:15';
SELECT * FROM RestaurantChain WHERE RestaurantID = 1;
COMMIT TRANSACTION;

-- Solution : -- Set isolation level to READ COMMITTED
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- Non Repeteable Reads: Transaction 2
use Test
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
BEGIN TRANSACTION;
SELECT * FROM RestaurantChain WHERE RestaurantName = 'Non-Repeteable-Reads';
WAITFOR DELAY '00:00:15';
SELECT * FROM RestaurantChain WHERE RestaurantName = 'Non-Repeteable-Reads';
COMMIT TRANSACTION;

-- SOLUTION : Set isolation level to REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;


-- Phantom Reads Transaction 2
use Test
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
BEGIN TRANSACTION;
SELECT * FROM RestaurantChain 
WAITFOR DELAY '00:00:10';
SELECT * FROM RestaurantChain 
COMMIT TRANSACTION;

-- SOLUTION : Set isolation level to SERIALIZABLE and make another select after transaction 1 and 2
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;


