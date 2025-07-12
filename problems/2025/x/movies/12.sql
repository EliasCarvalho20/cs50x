WITH
    movies_cte AS (
        SELECT
            s.movie_id,
            COUNT(s.person_id) AS stars
        FROM
            stars s
        WHERE
            s.person_id IN (
                SELECT
                    p.id
                FROM
                    people p
                WHERE
                    p.name IN ('Bradley Cooper', 'Jennifer Lawrence')
            )
        GROUP BY
            s.movie_id
        HAVING
            stars = 2
    )
SELECT
    m.title
FROM
    movies m
        INNER JOIN movies_cte m_cte ON m.id = m_cte.movie_id;