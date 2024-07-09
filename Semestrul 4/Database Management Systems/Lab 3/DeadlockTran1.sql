use Test

INSERT INTO RestaurantChain ( RestaurantName, Adress, Phone, MichelinStars)
VALUES ( 'Deadlock', '123 Main St', '555-5555', 1);
INSERT INTO Cook ( FirstName, LastName, Specialization)
VALUES ( 'Dead', 'Lock', 'ASD');

DELETE FROM RestaurantChain
WHERE RestaurantName = 'Deadlock';
DELETE FROM Cook
WHERE FirstName = 'Dead';


-- Transaction 1
BEGIN TRANSACTION;
UPDATE Cook SET Specialization = 'Grill' WHERE FirstName = 'Dead';
WAITFOR DELAY '00:00:10';
UPDATE RestaurantChain SET MichelinStars = 3 WHERE RestaurantName = 'Deadlock';
COMMIT TRANSACTION;


Select * From LogTable
-- Transaction 1 with logging
BEGIN TRY
    BEGIN TRANSACTION;
    UPDATE Cook SET Specialization = 'Grill' WHERE FirstName = 'Dead';
    WAITFOR DELAY '00:00:10';
    UPDATE RestaurantChain SET MichelinStars = 3 WHERE RestaurantName = 'Deadlock';

    COMMIT TRANSACTION;
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 1', GETDATE(), 'Transaction successful');
END TRY
BEGIN CATCH
    -- Handle the error and rollback if necessary
    IF XACT_STATE() <> 0
    BEGIN
        ROLLBACK TRANSACTION;
    END
    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 1', GETDATE(), ERROR_MESSAGE());
END CATCH;
