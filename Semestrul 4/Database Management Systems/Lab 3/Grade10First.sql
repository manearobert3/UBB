USE Test;

BEGIN TRY
	BEGIN TRANSACTION;
	SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
	UPDATE Cook SET Specialization = 'Sushi' WHERE CookID = 1;
	WAITFOR DELAY '00:00:10';
	COMMIT TRANSACTION;
	INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Commit', 'Transaction 1 Update Conflict', GETDATE(), 'Transaction successful');
	END TRY
BEGIN CATCH
    -- Handle the error and rollback if necessary
    IF XACT_STATE() <> 0
    BEGIN
        ROLLBACK TRANSACTION;
    END
    -- Log the error after handling the transaction state
    INSERT INTO LogTable (TypeOperation, TableOperation, ExecutionDate, ErrorMessage)
    VALUES ('Error', 'Transaction 1 Update Conflict', GETDATE(), ERROR_MESSAGE());
END CATCH;


-- without log
BEGIN TRANSACTION;
	SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
	UPDATE Cook SET Specialization = 'Sushi' WHERE CookID = 1;
	WAITFOR DELAY '00:00:10';
	COMMIT TRANSACTION;
