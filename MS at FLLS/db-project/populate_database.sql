BEGIN;

INSERT INTO "User" ("username", "email", "password_hash", "first_name", "last_name")
VALUES
    ('Kripton2005', 'verde.cristian2005@gmail.com', 'VXoIuc', 'Cristian', 'Verde'),
    ('Oepeling', 'livia.magureanu@gmail.com', '2zA+Ti', 'Livia', 'Magureanu'),
    ('adrian', 'budau.adi@gmail.com', 'JuKbUd', 'Adrian', 'Budau');


INSERT INTO "UserExt" ("user_id", "codeforces", "infoarena", "varena")
VALUES
    (2, 'livlivi', 'livlivi', 'livlivi');


INSERT INTO "Author" ("name", "user_id")
VALUES
    ('Livia Magureanu', 2),
    ('Cristian Verde', 1);

INSERT INTO "Author" ("name")
VALUES
    ('Alexandru Luchianov'),
    ('Matteo Verzotti');


INSERT INTO "Stage" ("name", "index")
VALUES
    ('Stage 1', 1),
    ('Stage 2', 2),
    ('Stage 3', 3),
    ('Stage 4', 4),
    ('Stage 5', 5),
    ('Stage 6', 6),
    ('Stage 7', 7),
    ('Stage 8', 8);


INSERT INTO "Task" ("title", "source", "link", "solution", "tags", "hints")
VALUES
    ('Boom', 'Infoarena', 'https://infoarena.ro/problema/boom', 'https://infoarena.ro/job_detail/1443712?action=view-source', 'Dijkstra, Dinamica pe stari exponentiale', false);

INSERT INTO "Task" ("title", "source", "link", "hints")
VALUES
    ('Tree2', 'Infoarena', 'https://infoarena.ro/problema/tree2', false);


INSERT INTO "Topic" ("name", "topo_order", "supertopic_id")
VALUES
    ('~', '~', NULL),
    ('Algebra', '~ / Algebra', 1),
        ('Fundamentals', '~ / Algebra / Fundamentals', 2),
        ('Prime Numbers', '~ / Algebra / Prime Numbers', 2),
        ('Number-theoretic functions', '~ / Algebra / Number-theoretic functions', 2),
        ('Modular arithmetic', '~ / Algebra / Modular arithmetic', 2),
        ('Number systems', '~ / Algebra / Number systems', 2),
        ('Miscellaneous', '~ / Algebra / Miscellaneous', 2),
        ('Linear Algebra', '~ / Algebra / Linear Algebra', 2),
            ('Matrices', '~ / Algebra / Linear  / Matrices', 9),
        ('Polynomials', '~ / Algebra / Groups, Rings and Fields', 2),
        ('Groups, Rings and Fields', '~ / Algebra / Fundamentals', 2),
        ('Power series and generator functions', '~ / Algebra / Power series and generator functions', 2),
    ('Data Structures', '~ / Data Structures', 1),
        ('Fundamentals', '~ / Data Structures / Fundamentals', 14),
        ('Fundamentals', '~ / Data Structures / Trees', 14),
        ('Fundamentals', '~ / Data Structures / STL', 14),
        ('Fundamentals', '~ / Data Structures / Advanced', 14),
    ('Dynamic Programming', '~ / Dynamic Programming', 1),
        ('Basics', '~ / Dynamic Programming / Basics', 19),
        ('DP optimizations', '~ / Dynamic Programming / DP optimizations', 19),
        ('Tasks', '~ / Dynamic Programming / Tasks', 19),
    ('String Processing', '~ / String Processing', 1),
        ('Fundamentals', '~ / String Processing / Fundamentals', 23),
        ('Advanced', '~ / String Processing / Advanced', 23),
        ('Tasks', '~ / String Processing / Tasks', 23),
    ('Combinatorics', '~ / Combinatorics', 1),
        ('Fundamentals', '~ / Combinatorics / Fundamentals', 27),
        ('Techniques', '~ / Combinatorics / Techniques', 27),
        ('Tasks', '~ / Combinatorics / Tasks', 27),
    ('Numerical', '~ / Numerical', 1),
        ('Search', '~ / Numerical / Search', 31),
            ('Binary Search', '~ / Numerical / Binary Search', 32),
        ('Integration', '~ / Numerical / Integration', 31),
    ('Geometry', '~ / Geometry', 1),
        ('Elementary operations', '~ / Geometry / Elementary operations', 35),
        ('Polygons', '~ / Geometry / Polygons', 35),
        ('Convex hull', '~ / Geometry / Convex hull', 35),
        ('Sweep-line', '~ / Geometry / Sweep-line', 35),
        ('Miscellaneous', '~ / Geometry / Miscellaneous', 35),
    ('Graphs', '~ / Graphs', 1),
        ('Graph traversal', '~ / Graphs / Graph traversal', 41),
        ('Connected components, bridges, articulations points', '~ / Graphs / Connected components, bridges, articulations points', 41),
        ('Single-source shortest paths', '~ / Graphs / Single-source shortest paths', 41),
        ('All-pairs shortest paths', '~ / Graphs / All-pairs shortest paths', 41),
        ('Trees', '~ / Graphs / Trees', 41),
        ('Cycles', '~ / Graphs / Cycles', 41),
        ('Lowest common ancestor', '~ / Graphs / Lowest common ancestor', 41),
        ('Flows and related problems', '~ / Graphs / Flows and related problems', 41),
        ('Matchings and related problems', '~ / Graphs / Matchings and related problems', 41),
        ('Miscellaneous', '~ / Graphs / Miscellaneous', 41),
    ('Miscellaneous', '~ / Miscellaneous', 1),
        ('Sequences', '~ / Miscellaneous / Sequences', 52),
        ('Game Theory', '~ / Miscellaneous / Game Theory', 52),
    ('Greedy', '~ / Greedy', 1),
        ('Basics', '~ / Greedy / Basics', 55),
    ('Spanning trees', '~ / Graphs / Trees / Spanning trees', 46);

INSERT INTO "Lesson" ("title", "author_id", "stage_id", "topic_id")
VALUES
    ('Introducere in grafuri', 1, 4, 41),
    ('Recursivitate', 2, 3, 1),
    ('DFS', 2, 4, 42),
    ('Introducere in arbori', 1, 4, 46),
    ('Arbori binari', 1, 4, 46),
    ('AINT', 1, 4, 46),
    ('Sortare', 2, 3, 1),
    ('Struct', 2, 3, 1),
    ('Sortarea structurilor', 2, 3, 1),
    ('Introducere in geometrie', 3, 3, 35),
    ('Baleiere', 2, 5, 39),
    ('Probleme cu baleiere si AINT', 2, 6, 39);

INSERT INTO "Edge" ("src_id", "dest_id")
VALUES
    (1, 3),
    (2, 3),
    (1, 4),
    (4, 5),
    (5, 6),
    (7, 9),
    (8, 9),
    (10, 11),
    (11, 12),
    (6, 12);

INSERT INTO "Lesson_Tasks" (lesson_id, task_id) VALUES (1, 2);

INSERT INTO "DoneTasks" (task_id, user_id) VALUES (2, 3);

INSERT INTO "CompletedLessons" (in_progress, lesson_id, user_id) VALUES (false, 1, 3);

COMMIT;