import { Room, TicTacToe, SidePick, Board, Pick, Turn, DecodedJWT, Result, Winner, BoardPick } from "../types/types"; 
import { useSocket } from "../hooks/useSocket";
import { useEffect, useRef, useState, MouseEvent } from "react";
import styled from 'styled-components';
import { useRouter } from "next/router";
import { checkTTTWinner, copyTuple, emptyBoard as initBoard, getOppositeSide } from "../utils/utils";
import Cookies from "js-cookie";
import { useAuthContext } from "../lib/authContext";
import jwtDecode from "jwt-decode";

const Container = styled.div`
  width: 100%;
  height: 100%;
  display: flex;
`;

const Choice = styled.div`
  position: relative;
  width: 100%;
  height: 50%;
  font-size: 15rem;
  font-family: Helvetica;
  text-align: center;
  background: teal;

  &:nth-child(odd) {
    background: #705e4b;
  }
  &:nth-child(even) {
    background: #8c7760;
  }
`;

const BoxContainer = styled.div`
  width: 400px;
	height: 400px;
	margin: 0 auto;
  background-color: #98795a;
  border: 6px solid #98795a;
  color: #fff;
  border-radius: 10px;
	display: grid;
	grid-template: repeat(3, 1fr) / repeat(3, 1fr);
`;

const Box = styled.div`
  border: 6px solid #98795a;
  background-color: #e2b17c;
  color: #705e4b;
  border-radius: 2px;
  font-family: Helvetica;
  font-weight: bold;
  font-size: 4em;
  display: flex;
  justify-content: center;
  align-items: center;
  user-select: none;
`;

const Cross = styled.div`
  width: 30px;
  height: 30px;
  font-size: 1.5rem;
  cursor: pointer;
  z-index: 1;
  position: absolute;
  right: 3px;
  bottom: 10px;
`;

const GameData = styled.div`
  width: 25%;
  height: 100%;
  border: 1px solid black;
`;

const GameContainer = styled.div`
  width: 75%;
  margin: 0 auto;
  display: flex;
  background: #e6be94;
  flex-direction: column;
  justify-content: center;
`;

const MiddleNick = styled.div`
  position: absolute;
  bottom: 50%;
  background: rgba(230, 190, 148, 0.5);
  width: 100%;
  font-size: 2rem;
  text-align: center;
  overflow-wrap: break-word;
`;

const CommunicateBox = styled.div`
  text-align: center;
  margin-bottom: 1rem;
`;

const Cloud = styled.div`
  background: #98795a;
  width: 20%;
  margin: 0.5rem auto 0 auto;
  color: #e6be94;
  font-weight: 500;
  font-family: Arial, Helvetica, sans-serif;
  padding: 0.3rem;
  cursor: pointer;
  border: 1px solid black;
  border-radius: 5px;
`;

type Players = {
  circlePlayer: TicTacToe["circlePlayer"],
  crossPlayer: TicTacToe["crossPlayer"]
}

const initPlayers: Players = {
  circlePlayer: null,
  crossPlayer: null
} as const;

const initWinner = {
  winner: null,
  surrender: false
} as const;

const TicTacToeGame = ({ room, password }: { room: Room, password: string }) => {
  const socket = useSocket();
  const router = useRouter();
  const { room: roomId } = router.query;
  const [players, setPlayers] = useState(initPlayers);
  const [game, setGame] = useState<Board>(initBoard);
  const [turn, setTurn] = useState<Turn>(null);
  const [winner, setWinner] = useState<{winner: Winner, surrender: boolean}>(initWinner);
  const { setIsAuthorized } = useAuthContext();
  const turnRef = useRef<Turn>(turn);
  const playersRef = useRef<Players>(players);
  const passwordRef = useRef(password);

  const jwt = Cookies.get("token");
  if (!jwt) {
    setIsAuthorized(false);
    throw new Error("unauthorized");
  }
  const data = jwtDecode<DecodedJWT>(jwt);

  const setTurnWrapper = (side: string | null) => {
    if (side === null) return setTurn(null);
    side = side?.charAt(0).toLowerCase() + side?.slice(1);
    setTurn(side as Turn);
  }

  const play = (side: Turn) => {
    setGame(initBoard);
    setWinner({
      winner: null,
      surrender: false
    });
    setTurnWrapper(side);
  }

  useEffect(() => {
    socket?.on("roomData", (room) => {
      setGame(room.game.board.map((pick: number) => pick === 1 ? "O" : pick === 0 ? "X" : null));
      setTurnWrapper(room.game.turn);
      setPlayers({
        circlePlayer: room.game.circlePlayer,
        crossPlayer: room.game.crossPlayer
      });
      const winner = checkTTTWinner(room.game.board);
      if (winner && typeof players[winner] === "string") {
        setWinner({ winner: [winner, players[winner] || ""], surrender: false});
      }
    })

    socket?.on("sidePicked", (side, player) => {
      side = side.charAt(0).toLowerCase() + side.slice(1);
      const oppositeSide = getOppositeSide(side);
      if (winner.winner) setWinner(initWinner);
      if (player !== null && playersRef.current[oppositeSide] === player) {
        setPlayers({ ...playersRef.current, [side]: player, [oppositeSide]: null });
      } else {
        setPlayers({ ...playersRef.current, [side]: player });
      }
    });

    socket?.on("startGame", (side) => {
      play(side);
    });

    socket?.on("move", (i, pick) => {
      setGame(prevGame => {
        const copy = copyTuple(prevGame);
        copy[i] = pick === 1 ? "O" : "X";
        return copy;
      });

      if (turnRef.current) {
        setTurnWrapper(getOppositeSide(turnRef.current));
      }
    });

    socket?.on("winner", (winner, surr = false) => {
      const result = ["crossPlayer", "circlePlayer", "draw"][winner.result];

      setWinner({ winner: [result as Result, winner.player], surrender: surr });
      setTurnWrapper(null);
    });

    socket?.on("stopGame", () => {
      setGame(initBoard);
      setWinner(initWinner);
      setTurnWrapper(null);
    });

    if (typeof roomId === "string" && !room.data.requiresPassword) {
      if (!room.data.requiresPassword) {
        socket?.invoke("GetRoom", roomId, undefined, jwt);
      }
    }
  }, [jwt, players, socket, roomId, room.data.requiresPassword, winner.winner])
  
  useEffect(() => {
    if (typeof roomId === "string")
      socket?.invoke("GetRoom", roomId, passwordRef.current, jwt);
  }, [jwt, roomId, socket])
  
  useEffect(() => {
    playersRef.current = players;
  }, [players]);

  useEffect(() => {
    turnRef.current = turn;
  }, [turn]);

  useEffect(() => {
    const exitingFunction = () => {
      socket?.invoke("HandleLeave");
    };

    router.events.on('routeChangeStart', exitingFunction );

    return () => {
      router.events.off('routeChangeStart', exitingFunction);
    };
  }, [players, router.events, jwt, socket]);

  const handleChoice = (type: Pick) => {
    const side = type === "O" ? "circlePlayer" : "crossPlayer";
    if (players[side] === null && typeof roomId === "string") {
      socket?.invoke("PickSide", roomId, side, jwt);
    }
  }

  const handleClick = (e: MouseEvent<HTMLDivElement>) => {
    const data = e.currentTarget.getAttribute("data-id");
    if (turn === null) return;
    if (data) {
      const index = Number(data);
      if (game[index] === null && typeof roomId === "string") {
        socket?.invoke("Move", roomId, index, jwt);
      }
    }
  }

  const generateMessage = (winner: Result, winnerNick: string, surr: boolean) => {
    if (winner === "draw") {
      return `It's a draw!`
    } else if (winner) {
      return `${winnerNick} is the winner!${ surr ? ` Their oponent surrendered!` : ""}`;
    }
  }

  const restart = () => {
    if (typeof roomId === "string")
    socket?.invoke("Restart", roomId);
  }

  const canLeave = (side: SidePick) => {
    if (!room?.data.owner) return false;
    return data.nick === room.data.owner || data.nick === players[side];
  }
  
  const leave = (pick: Pick) => {
    const side = pick === "O" ? "circlePlayer" : "crossPlayer";
    if (canLeave(side) && typeof roomId === "string") {
      socket?.invoke("Kick", side, roomId, jwt);
    }
  }

  const arePlayersReady = () => players["crossPlayer"] && players["circlePlayer"];

  return (
    <Container>
      <GameData>
        <Choice onClick={() => handleChoice("O")}>
          <>
            O
            { players["circlePlayer"] && <MiddleNick>{players["circlePlayer"]}</MiddleNick>}
            { canLeave("circlePlayer") && <Cross onClick={() => leave("O")}>x</Cross> }
          </>
        </Choice>
        <Choice onClick={() => handleChoice("X")}>
          <>
            X 
            { players["crossPlayer"] && <MiddleNick>{players["crossPlayer"]}</MiddleNick>}
            { canLeave("crossPlayer") && <Cross onClick={() => leave("X")}>x</Cross> }
          </>
        </Choice>
      </GameData>
      <GameContainer>
        <CommunicateBox>
          { turn && arePlayersReady() && (<h3>It&apos;s {players[turn]} turn!</h3>)}
          { winner.winner && arePlayersReady() && 
              <h3>{generateMessage(winner.winner[0], winner.winner[1], winner.surrender)}</h3>}
          { !turn && !arePlayersReady() && (<h3>Waiting for players...</h3>)}
          { !turn && arePlayersReady() && <Cloud onClick={restart}>Play again</Cloud> }
        </CommunicateBox>
        <BoxContainer>
          {
            game.map((pick, index) => <Box data-id={index} onClick={handleClick} key={index}>{pick}</Box>)
          }
        </BoxContainer>
      </GameContainer>
    </Container>
  )
}

export default TicTacToeGame;