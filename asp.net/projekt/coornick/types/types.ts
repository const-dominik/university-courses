export type UserData = {
  email: string;
  password: string;
  nick: string;
  stats: [wins: number, draws: number, loses: number]
}

export type ProfileData = {
  nick: string;
  stats: UserData["stats"]
}

export type RegisterData = {
  email: string;
  password: string;
  nick: string;
}

export type LoginData = {
  identifier: string //nick or email
  password: string
}

export type GuestData = {
  nick: string;
  exp: number; //Date
}

export type DecodedJWT = {
  email?: string;
  nick: string;
  exp: number;
}

export type RoomsWithId = { key: string, data: RoomData }[]

export type Turn = SidePick | null;
export type SidePick = "crossPlayer" | "circlePlayer";
export type Result = SidePick | "draw";
export type Winner = [Result, string] | null;
export type Pick = "X" | "O";
export type BoardPick = Pick | null;
export type Board = [BoardPick, BoardPick, BoardPick, BoardPick, BoardPick, BoardPick, BoardPick, BoardPick, BoardPick];

export type TicTacToe = {
  crossPlayer: string | null;
  circlePlayer: string | null;
  turn: SidePick | null;
  board: Board;
}

export type RoomData = {
  name: string;
  owner: string;
  requiresPassword: boolean;
  password?: string;
}

export type Room = {
  data: RoomData;
  id: string;
  game: TicTacToe;
}
