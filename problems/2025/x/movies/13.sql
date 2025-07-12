WITH
    movies_cte AS (
        SELECT
            s.movie_id
        FROM
            stars s
        WHERE
            s.person_id = (
                SELECT
                    p.id
                FROM
                    people p
                WHERE
                    p.name = 'Kevin Bacon'
                  AND p.birth = 1958
            )
    ),
    people_cte AS (
        SELECT
            s.person_id
        FROM
            stars s
        WHERE
            s.movie_id IN (
                SELECT
                    m_cte.movie_id
                FROM
                    movies_cte m_cte
            )
    )
SELECT
    p.name
FROM
    people p
        INNER JOIN people_cte p_cte ON p.id = p_cte.person_id
WHERE
    p.name != 'Kevin Bacon';