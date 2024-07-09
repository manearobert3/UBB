-- Dirty Reads: Transaction 1 Dirty reads occur when a transaction reads data that has been written by another transaction but not yet committed.
use Test
BEGIN TRANSACTION;
UPDATE RestaurantChain SET MichelinStars = 3 WHERE RestaurantID = 1;
WAITFOR DELAY '00:00:10';
ROLLBACK TRANSACTION;
SELECT * FROM LogTable


-- Non Repeteable Reads: Non-repeatable reads occur when a transaction reads a row, and another transaction modifies or deletes that row, 
-- causing the initial transaction to see different data if it reads the same row again.
INSERT INTO RestaurantChain ( RestaurantName, Adress, Phone, MichelinStars)
VALUES ( 'Non-Repeteable-Reads', '123 Main St', '555-5555', 2);


DELETE FROM RestaurantChain
WHERE RestaurantName = 'Non-Repeteable-Reads';


-- Non Repeteable Reads: Transaction 1 
BEGIN TRANSACTION;
WAITFOR DELAY '00:00:10';
UPDATE RestaurantChain SET MichelinStars = 4 WHERE RestaurantName = 'Non-Repeteable-Reads';
COMMIT TRANSACTION;



-- Phantom Reads Transaction 1 Phantom reads occur when a transaction re-executes a query and finds rows that were not visible before.
BEGIN TRANSACTION;
WAITFOR DELAY '00:00:10';
INSERT INTO RestaurantChain ( RestaurantName, Adress, Phone, MichelinStars)
VALUES ( 'Phantom-Reads1', '123 Main St', '555-5555', 2);
COMMIT TRANSACTION





-- NON Repeteable Reads with logging:
Select * from LogChanges
use Test
BEGIN TRY
    BEGIN TRANSACTION;

    -- Log the old value before the update
    DECLARE @oldData INT;
    DECLARE @newData INT;
    SELECT @oldData = MichelinStars FROM RestaurantChain WHERE RestaurantName = 'Non-Repeteable-Reads';

    -- Perform the update
	WAITFOR DELAY '00:00:10';
	UPDATE RestaurantChain SET MichelinStars = 4 WHERE RestaurantName = 'Non-Repeteable-Reads';
	SELECT @newData = MichelinStars FROM RestaurantChain WHERE RestaurantName = 'Non-Repeteable-Reads';
	EXEC log_changes2 @oldData, @newData, 'Transaction 1 Dirty Reads: Update RestaurantChain',NULL;

	COMMIT TRANSACTION;
    -- Log the new value after the update


    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 1 Dirty Reads', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH

    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 1 Dirty Reads', GETDATE(), ERROR_MESSAGE());
END CATCH;






-- Phantom Reads Transaction 1 with logging:
Select * from LogChanges
use Test
BEGIN TRY
    BEGIN TRANSACTION;


    -- Log the old value before the update
    DECLARE @oldData INT;
    DECLARE @newData INT;
    SELECT @oldData = NULL ;

    -- Perform the update
	WAITFOR DELAY '00:00:10';
	INSERT INTO RestaurantChain ( RestaurantName, Adress, Phone, MichelinStars)
	VALUES ( 'Phantom-Reads1', '123 Main St', '555-5555', 2);
	SELECT @newData = MichelinStars FROM RestaurantChain WHERE RestaurantName = 'Phantom-Reads1';
	EXEC log_changes2 @oldData, @newData, 'Transaction 1 Phantom Reads: Insert in RestaurantChain',NULL;

	COMMIT TRANSACTION;
    -- Log the new value after the update


    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 1 Dirty Reads', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH

    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 1 Dirty Reads', GETDATE(), ERROR_MESSAGE());
END CATCH;
