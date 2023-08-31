# DuoAlgo — Database

Link la acest [proiect](https://github.com/Oepeling/University-Work/tree/master/MS%20at%20FLLS/db-project).

## 1. Prezentarea bazei de date

Baza de date prezentata corespunde unei aplicatii web al carei scop este facilitarea invatarii programarii competitive pe cont propriu. Entitatea de baza a aplicatiei, in jurul careia e construita toata baza de date, o reprezinta lectiile.

### 1.1. Diagrama
![](https://paper-attachments.dropboxusercontent.com/s_906DB4F502DD484302B3D1A7F0BCFE9EFF7493A3971BBC78FAAF70EFFC342DDB_1686923648505_Pinguin+Beautinator.png)

### 1.2. Descrierea entitatilor

**User**

- `id` — primary key, autogenerat (incremental)
- `username` — unique, not null
- `email` — unique, not null
- `password_hash` — not null, generat din front-end
- `first_name` — poate fi null
- `last_name` — poate fi null

Tabel de baza pentru user cu scop de autentificare.

**UserExt**

- `user_id` — primary key, foreign key
    - relatie one-to-one cu **User**
    - unique, not null
- `codeforces` — handle pe [codeforces.com](https://codeforces.com)
- `infoarena` — handle pe [infoarena.ro](https://infoarena.ro)
- `varena` — handle pe [nerdarena.ro](https://www.nerdarena.ro) (se numea varena.ro pana de curand)

Tabel cu informatii aditionale pentru un user cu scopul de a urmari progresul lor la task-urile propuse de aplicatie.

**Author**

- `id` — primary key, autogenerat (incremental)
- `name` — numele autorului (complet sau in ce format vrea el sa apara)
- `user_id` — foreign key 
    - relatie one-to-one cu **User**
    - unique, optional

Majoritatea lectiilor vor avea un autor pentru a recunoaste meritele celor care contribuie la aplicatie.

**Topic**

- `id` — primary key, autogenerat (incremental)
- `name` — not null, denumirea topicului
- `supertopic` — foreign key
    - relatie many-to-one cu **Topic**
    - optional
    - topicul mai mare de care apartine un subtopic
- `topo_order` — not null, generat din front-end
    - reprezinta path-ul topicurilor (de la radacina) pana la un topic

Contine majoritatea topicurilor cunoscute si studiate in programarea competitiva, structurate sub forma unui arbore. Nu este un tabel care se modifica foarte des, ideal toata informatia din tabel este inserata la initial si modificata doar in caz de nevoie.
In practica, singura intrare care nu va avea un supertopic (parinte) este o radacina fictiva creata cu scopul de a face sortarea topologica mai usoara.

**Stage**

- `id` — primary key, autogenerat (incremental)
- `name` — numele etapei de studii
- `index` — numarul de ordine al etapei de studii

Lectiile sunt impartite pe etape de studii care sunt gandite pentru a fi parcurse in ordine. In design-ul actual al materiei, exista 8 etape care corespund claselor din a 5a pana intr-a 12a si impart materia intr-un mod echilibrat pentru o persoana care incepe informatica in scoala gimnaziala. Acestea pot fi parcurse si mai rapid intrucat nu exista o restrictie in acest sens.

**Lesson**

- `id` — primary key, autogenerat (incremental)
- `title` — not null, titlul lectiei
- `topic_id` — foreign key
    - relatie many-to-one la **Topic**
    - not null, topicul de cara apartine o lectie
- `stage_id` — foreign key
    - relatie many-to-one la **Stage**
    - not null, etapa de studii de care tine o lectie
- `duration` — optional, durata estimata de a parcurge si intelege o lectie
- `content` — continutul unei lectii
    - optional (pentru a da optiunea autorului de a completa / edita ulterior)
    - teoretic in format `.md`
- `link_to_code` — optional, link la cod model pentru algoritmul predat
- `author_id` — foreign key
    - relatie many-to-one la **Author**
    - optional, autorul lectiei

Unitatea de baza a aplicatiei.

**Task**

- `id` — primary key, autogenerat (incremental)
- `title` — not null, titlul problemei propuse
- `source` — not null, website-ul de pregatire de pe care provine problema
- `link` — not null, link-ul la problema pe website-ul de pe care este luata
- `description` — optional, scurta descriere a problemei
- `solution` — optional, link la cod sursa model pentru rezolvarea problemei
- `tags` — optional, tag-uri de materie care corespund problemei
- `hints` — not null, boolean, true daca exista un sistem de pana in 3 hint-uri progresive pentru rezolvarea problemei
- `hint1`, `hint2`, `hint3` — optionale, hint-uri progresive pentru rezolvarea problemei

Lectiile pot veni cu o lista de probleme sugerate pentru a exersa notiunile invatate. Rezolvarea acestor probleme de catre un utilizator este monitorizata pentru cele 3 website-uri agregate (codeforces, infoarena, varena).


### 1.3. Descrierea tabelelor pentru relatiile many-to-many

**Lesson_Tasks**

- `id` — primary key, autogenerat (incremental)
- `lesson_id` — foreign key
    - relatie many-to-one la **Lesson**
    - not null
- `task_id` — foreign key
    - relatie many-to-one la **Task**
    - not null
- constrangere: perechea `(lesson_id, task_id)` este unique

Simuleaza relatia many-to-many care descrie ce task-uri sunt recomandate la fiecare lectie. Un task poate fi recomandat pentru mai multe lectii.

**DoneTasks**

- `id` — primary key, autogenerat (incremental)
- `user_id` — foreign key
    - relatie many-to-one la **User**
    - not null
- `task_id` — foreign key
    - relatie many-to-one la **Task**
    - not null
- constrangere: perechea `(user_id, task_id)` este unique

Simuleaza relatia many-to-many care descrie ce probleme au fost rezolvate de un user.

**CompletedLessons**

- `id` — primary key, autogenerat (incremental)
- `in_progress` — not null, boolean, true daca lectia nu a fost inca parcursa complet
- `lesson_id` — foreign key
    - relatie many-to-one la **Lesson**
    - not null
- `user_id` — foreign key
    - relatie many-to-one la **User**
    - not null
- constrangere: perechea `(lesson_id, user_id)` este unique

Simuleaza relatia many-to-many care descrie ce lectii au fost parcurse / sunt parcurse in acest moment de un user.

## 2. Implementare
### 2.1. Crearea tabelelor

```pgsql
BEGIN;

--
-- Clear database
--
DROP TABLE IF EXISTS "Edge";
DROP TABLE IF EXISTS "Lesson_Tasks";
DROP TABLE IF EXISTS "CompletedLessons";
DROP TABLE IF EXISTS "DoneTasks";
DROP TABLE IF EXISTS "Task";
DROP TABLE IF EXISTS "UserExt";
DROP TABLE IF EXISTS "Lesson";
DROP TABLE IF EXISTS "Author";
DROP TABLE IF EXISTS "Stage";
DROP TABLE IF EXISTS "Topic";
DROP TABLE IF EXISTS "User";

--
-- Create model user
--
CREATE TABLE "User" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "username" varchar(50) NOT NULL UNIQUE,
    "email" varchar(50) NOT NULL UNIQUE,
    "password_hash" varchar(100) NOT NULL,
    "first_name" varchar(50), "last_name" varchar(50));

--
-- Create model UserExt
--
CREATE TABLE "UserExt" (
    "user_id" integer NOT NULL PRIMARY KEY,
    "codeforces" varchar(50) NULL,
    "infoarena" varchar(50) NULL,
    "varena" varchar(50) NULL);

ALTER TABLE "UserExt" ADD CONSTRAINT "UserExt_User_id_fk_User_id"
    FOREIGN KEY ("user_id") REFERENCES "User" ("id") DEFERRABLE INITIALLY DEFERRED;

--
-- Create model Author
--
CREATE TABLE "Author" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "name" varchar(50) NOT NULL,
    "user_id" integer NULL UNIQUE);

ALTER TABLE "Author" ADD CONSTRAINT "Author_user_id_fk_User_id"
    FOREIGN KEY ("user_id") REFERENCES "User" ("id") DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Author_user_id" ON "Author" ("user_id");

--
-- Create model Stage
--
CREATE TABLE "Stage" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "name" varchar(50) NOT NULL,
    "index" integer NOT NULL UNIQUE);

--
-- Create model Topic
--
CREATE TABLE "Topic" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "name" varchar(100) NOT NULL,
    "topo_order" varchar(200) NOT NULL,
    "supertopic_id" integer NULL);

ALTER TABLE "Topic" ADD CONSTRAINT "Topic_supertopic_id_fk_Topic_id"
    FOREIGN KEY ("supertopic_id") REFERENCES "Topic" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Topic_supertopic_id" ON "Topic" ("supertopic_id");

--
-- Create model Task
--
CREATE TABLE "Task" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "title" varchar(50) NOT NULL,
    "source" varchar(50) NOT NULL,
    "description" text NULL,
    "link" varchar(200) NOT NULL UNIQUE,
    "solution" varchar(200) NULL,
    "tags" text NULL,
    "hints" boolean NOT NULL DEFAULT false,
    "hint1" text NULL, "hint2" text NULL, "hint3" text NULL);

CREATE INDEX "Task_link_like" ON "Task" ("link" varchar_pattern_ops);

--
-- Create model Lesson
--
CREATE TABLE "Lesson" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "title" varchar(100) NOT NULL,
    "duration" interval NULL,
    "content" text NULL,
    "link_to_code" varchar(200) NULL,
    "author_id" integer NULL,
    "stage_id" integer NOT NULL,
    "topic_id" integer NOT NULL);

ALTER TABLE "Lesson" ADD CONSTRAINT "Lesson_author_id_fk_Author_id"
    FOREIGN KEY ("author_id") REFERENCES "Author" ("id")
        ON DELETE SET NULL DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Lesson_author_id" ON "Lesson" ("author_id");

ALTER TABLE "Lesson" ADD CONSTRAINT "Lesson_stage_fk_Stage_id"
    FOREIGN KEY ("stage_id") REFERENCES "Stage" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Lesson_stage_id" ON "Lesson" ("stage_id");

ALTER TABLE "Lesson" ADD CONSTRAINT "Lesson_topic_id_fk_Topic_id"
    FOREIGN KEY ("topic_id") REFERENCES "Topic" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Lesson_topic_id" ON "Lesson" ("topic_id");

CREATE INDEX "Lesson_link_like" ON "Lesson" ("link_to_code" varchar_pattern_ops);

--
-- Create model Lesson_Tasks
--
CREATE TABLE "Lesson_Tasks" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "lesson_id" integer NOT NULL,
    "task_id" integer NOT NULL);

ALTER TABLE "Lesson_Tasks" ADD CONSTRAINT "Lesson_Tasks_lesson_id_task_id_uniq"
    UNIQUE ("lesson_id", "task_id");

ALTER TABLE "Lesson_Tasks" ADD CONSTRAINT "Lesson_Tasks_lesson_id_fk_Lesson_id"
    FOREIGN KEY ("lesson_id") REFERENCES "Lesson" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Lesson_Tasks_lesson_id" ON "Lesson_Tasks" ("lesson_id");

ALTER TABLE "Lesson_Tasks" ADD CONSTRAINT "Lesson_Tasks_task_id_fk_Task_id"
    FOREIGN KEY ("task_id") REFERENCES "Task" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Lesson_Tasks_task_id" ON "Lesson_Tasks" ("task_id");

--
-- Create model Edge
--
CREATE TABLE "Edge" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "hidden" boolean NOT NULL DEFAULT false,
    "src_id" integer NOT NULL,
    "dest_id" integer NOT NULL);

ALTER TABLE "Edge" ADD CONSTRAINT "Edge_src_id_dest_id_uniq"
    UNIQUE ("src_id", "dest_id");

ALTER TABLE "Edge" ADD CONSTRAINT "Edge_dest_id_fk_Lesson_id"
    FOREIGN KEY ("dest_id") REFERENCES "Lesson" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Edge_dest_id" ON "Edge" ("dest_id");

ALTER TABLE "Edge" ADD CONSTRAINT "Edge_src_id_fk_Lesson_id"
    FOREIGN KEY ("src_id") REFERENCES "Lesson" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "Edge_src_id" ON "Edge" ("src_id");

--
-- Create model DoneTasks
--
CREATE TABLE "DoneTasks" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "task_id" integer NOT NULL,
    "user_id" integer NOT NULL);

ALTER TABLE "DoneTasks" ADD CONSTRAINT "DoneTasks_task_id_user_id_uniq"
    UNIQUE ("task_id", "user_id");

ALTER TABLE "DoneTasks" ADD CONSTRAINT "DoneTasks_task_id_fk_Task_id"
    FOREIGN KEY ("task_id") REFERENCES "Task" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "DoneTasks_task_id" ON "DoneTasks" ("task_id");

ALTER TABLE "DoneTasks" ADD CONSTRAINT "DoneTasks_user_id_fk_User_id"
    FOREIGN KEY ("user_id") REFERENCES "User" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "DoneTasks_user_id" ON "DoneTasks" ("user_id");

--
-- Create model CompletedLessons
--
CREATE TABLE "CompletedLessons" (
    "id" integer NOT NULL PRIMARY KEY GENERATED BY DEFAULT AS IDENTITY,
    "in_progress" boolean NOT NULL,
    "lesson_id" integer NOT NULL,
    "user_id" integer NOT NULL);

ALTER TABLE "CompletedLessons" ADD CONSTRAINT "CompletedLessons_lesson_id_user_id_uniq"
    UNIQUE ("lesson_id", "user_id");

ALTER TABLE "CompletedLessons" ADD CONSTRAINT "CompletedLessons_lesson_id_fk_Lesson_id"
    FOREIGN KEY ("lesson_id") REFERENCES "Lesson" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "CompletedLessons_lesson_id" ON "CompletedLessons" ("lesson_id");

ALTER TABLE "CompletedLessons" ADD CONSTRAINT "CompletedLessons_user_id_fk_User_id"
    FOREIGN KEY ("user_id") REFERENCES "User" ("id")
        ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED;
CREATE INDEX "CompletedLessons_user_id" ON "CompletedLessons" ("user_id");

COMMIT;
```

### 2.2. Popularea tabelelor

```pgsql
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
```

## 3. Model de interactiune cu baza de date
### 3.1. a)

Listare conținut cu posibilitatea de sortare în funcție de o opțiune citită de la tastatură;

**Enunt:**
Să se afișeze toate topicurile sortate dupa o coloana dată ca parametru.

**Cod:**

```pgsql
-- a)
SELECT *
FROM "Topic"
ORDER BY :_orderby;
```

### 3.2. b)

Afișarea rezultatului unei cereri care extrage informații din cel puțin 3 tabele şi filtrează rezultatul prin intermediul a cel puțin 2 condiții.

**Enunt:**
Sa se afiseze id-ul, titlul si index-ul stage-ului pentru lectiile scrise de *Alexandru Luchianov* care fac parte din *Stage 3*.

**Cod:**

```pgsql
-- b)
SELECT l.id, l.title, s.index
FROM "Lesson" AS l
INNER JOIN "Stage" AS s ON l.stage_id = s.id
INNER JOIN "Author" AS a ON l.author_id = a.id
WHERE a.name = 'Alexandru Luchianov' AND s.name = 'Stage 3';
```

### 3.3. c)

Afișarea rezultatului unei cereri care folosește funcții grup și o
clauza having.

**Enunt:**
Sa se afiseze autorii care au cel putin 2 lectii scrise si numarul de lectii al fiecaruia.

**Cod:**

```pgsql
SELECT COUNT(*), author_id FROM "Lesson"
GROUP BY author_id HAVING COUNT(author_id) > 2;
```

### 3.4. d)

Implementarea unei constrângeri de tipul on delete cascade.
Nota: deja implementata la crearea tabelului

### 3.5. e)

Rezolvarea unei interogări cu ajutorul unei subcereri.

**Enunt:**
Sa se afiseze lectiile care au proprietatea ca sunt singura lectie scrisa de autorul lor.

**Cod:**

```pgsql
-- e) 
SELECT l.id, l.title, a.name
FROM "Lesson" AS l
INNER JOIN "Author" AS a ON l.author_id = a.id
WHERE a.id in (
    SELECT author_id FROM "Lesson" GROUP BY author_id HAVING COUNT(*) = 1
);
```

