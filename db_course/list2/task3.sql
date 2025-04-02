DROP PROCEDURE IF EXISTS createReader 
GO

CREATE PROCEDURE createReader 
    @pesel CHAR(11), 
    @surname VARCHAR(30), 
    @birthdate DATE,
	@city VARCHAR(30)
AS
BEGIN
	-- calculate checksum to validate PESEL format
	IF LEN(@pesel) != 11
		THROW 50000, 'PESEL should have 11 characters', 0;
	
	DECLARE @weights VARCHAR(11) = '13791379131'
	DECLARE @i INT = 1
	DECLARE @checksum INT = 0
	DECLARE @actual_checksum INT = CAST(SUBSTRING(@pesel, 11, 1) as INT)

	WHILE @i <= 10
	BEGIN
		DECLARE @c CHAR = SUBSTRING(@pesel, @i, 1)
		DECLARE @weight INT = CAST(SUBSTRING(@weights, @i, 1) as INT)

		IF (@c < '0') OR (@c > '9')
			THROW 50000, 'PESEL should contain numbers only.', 0;

		SET @checksum += @weight * CAST(@c as INT)
		SET @i += 1
	END

	SET @checksum = @checksum % 10
	IF (@checksum != 0)
		SET @checksum = 10 - (@checksum)

	IF (@checksum != @actual_checksum)
		THROW 50000, 'PESEL format is invalid.', 0;

	-- check surname length and 1st letter capital
	IF LEN(@surname) < 2
		THROW 50000, 'surname too short', 0;

	IF LEFT(@surname, 1) != UPPER(LEFT(@surname, 1)) COLLATE Latin1_General_BIN
		THROW 50000, 'surname should start with capital letter', 0;

	-- check if birthdate is in correct format
	IF TRY_CAST(@birthdate as DATE) IS NULL
		THROW 50000, 'Birthdate cannot be casted to date', 0;

	INSERT INTO dbo.Czytelnik (PESEL, Nazwisko, Miasto, Data_Urodzenia)
		VALUES (@pesel, @surname, @city, @birthdate);
END
GO
-- correct
--EXEC createReader '12345678903', 'Smith', '2020-01-10', 'Wroc³aw';

--wrong pesel
--EXEC createReader '12345678902', 'Smith', '2020-01-10', 'Wroc³aw';

-- short surname
--EXEC createReader '12345678903', 'S', '2020-01-10', 'Wroc³aw';

-- lower case surname
-- EXEC createReader '12345678903', 'smith', '2020-01-10', 'Wroc³aw';

--wrong birthdate
--EXEC createReader '12345678903', 'Smith', 'asd', 'Wroc³aw';
--EXEC createReader '12345678903', 'Smith', '324920/234/23', 'Wroc³aw';
