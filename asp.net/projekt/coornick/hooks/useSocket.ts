import { HubConnectionsContext} from '../lib/socketContext'
import { useContext } from "react";

export const useSocket = () => {
  const socket = useContext(HubConnectionsContext);

  return socket;
};