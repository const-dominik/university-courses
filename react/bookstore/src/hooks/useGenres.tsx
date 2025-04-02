import { useQuery } from "@tanstack/react-query";

const fetchGenres = async () => {
    const genresResponse = await fetch(`http://localhost:3000/genres`);

    const genres = await genresResponse.json();

    return genres;
};

const useGenres = () => {
    return useQuery({
        queryKey: ["genres"],
        queryFn: fetchGenres,
    });
};

export default useGenres;
