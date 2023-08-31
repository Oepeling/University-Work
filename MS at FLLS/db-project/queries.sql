-- a)
SELECT *
FROM "Topic"
ORDER BY :_orderby;

-- b)
SELECT l.id, l.title, s.index
FROM "Lesson" AS l
INNER JOIN "Stage" AS s ON l.stage_id = s.id
INNER JOIN "Author" AS a ON l.author_id = a.id
WHERE a.name = 'Alexandru Luchianov' AND s.name = 'Stage 3';

-- c)
SELECT COUNT(*), author_id FROM "Lesson"
GROUP BY author_id HAVING COUNT(author_id) > 2;

-- e)
SELECT l.id, l.title, a.name
FROM "Lesson" AS l
INNER JOIN "Author" AS a ON l.author_id = a.id
WHERE a.id IN (
    SELECT author_id FROM "Lesson" GROUP BY author_id HAVING COUNT(*) = 1);