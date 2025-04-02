fn main() {
    println!("Hello, world!");
}

fn first_n_smallest(arr: &[i32], n: usize) -> Vec<i32> {
    if n == 0 {
        return vec![];
    }

    let mut vec = arr.to_vec();

    while vec.len() != n {
        if let Some(max_index) = vec
            .iter()
            .enumerate()
            .rev()
            .find(|&(_, &x)| x == *vec.iter().max().unwrap())
            .map(|(index, _)| index)
        {
            vec.remove(max_index);
        }
    }

    vec
}

#[test]
fn test_basic() {
    assert_eq!(first_n_smallest(&[1, 2, 3, 4, 5], 3), [1, 2, 3]);
    assert_eq!(first_n_smallest(&[5, 4, 3, 2, 1], 3), [3, 2, 1]);
    assert_eq!(first_n_smallest(&[1, 2, 3, 1, 2], 3), [1, 2, 1]);
    assert_eq!(first_n_smallest(&[1, 2, 3, -4, 0], 3), [1, -4, 0]);
    assert_eq!(first_n_smallest(&[1, 2, 3, 4, 5], 0), []);
    assert_eq!(first_n_smallest(&[1, 2, 3, 4, 5], 5), [1, 2, 3, 4, 5]);
    assert_eq!(first_n_smallest(&[1, 2, 3, 4, 2], 4), [1, 2, 3, 2]);
    assert_eq!(first_n_smallest(&[2, 1, 2, 3, 4, 2], 2), [2, 1]);
    assert_eq!(first_n_smallest(&[2, 1, 2, 3, 4, 2], 3), [2, 1, 2]);
    assert_eq!(first_n_smallest(&[2, 1, 2, 3, 4, 2], 4), [2, 1, 2, 2]);
}
