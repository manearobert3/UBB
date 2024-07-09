use Test
-- Transaction 2
 SET DEADLOCK_PRIORITY HIGH;
BEGIN TRANSACTION;
UPDATE RestaurantChain SET MichelinStars = 2 WHERE RestaurantName = 'Deadlock';
WAITFOR DELAY '00:00:10';
UPDATE Cook SET Specialization = 'Pastry' WHERE FirstName = 'Dead';
COMMIT TRANSACTION;


-- Solution: SET DEADLOCK_PRIORITY HIGH;
-- or execute the update on the same order




-- Transaction 2 with logging

BEGIN TRY
    BEGIN TRANSACTION;
    UPDATE RestaurantChain SET MichelinStars = 2 WHERE RestaurantName = 'Deadlock';
    WAITFOR DELAY '00:00:10';
    UPDATE Cook SET Specialization = 'Pastry' WHERE FirstName = 'Dead';

    COMMIT TRANSACTION;
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 2', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH
    -- Handle the error and rollback if necessary
    IF XACT_STATE() <> 0
    BEGIN
        ROLLBACK TRANSACTION;
    END
    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 2', GETDATE(), ERROR_MESSAGE());
END CATCH;
