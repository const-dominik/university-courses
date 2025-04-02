import * as React from 'react';
import { RoomData } from "../types/types"
import styled from 'styled-components';
import Link from 'next/link';
import Image from 'next/image';
import lock from '../public/lock.svg';
import unlock from '../public/unlock.svg';

type RoomLineProps = {
  room: { key: string, data: RoomData };
}

const NameDiv = styled.div`
  width: 50%;
`;
  
const OwnerDiv = styled.div`
  width: 40%;
`;
  
const LockDiv = styled.div`
  width: 10%;
`;

const StyledLink = styled(Link)`
  text-decoration: none;
  color: black;
  display: flexbox;
  padding: 4px;
  &:nth-child(odd) {
    background: #8c7760;
  }
  &:nth-child(even) {
    background: #705e4b;
  }
`;

const RoomLine = (props: RoomLineProps) => {
  const { key, data } = props.room;
  const { name, owner, requiresPassword } = data;

  return (
    <StyledLink href={`/${key}`} key={key}> 
      <NameDiv>{name}</NameDiv>
      <OwnerDiv>{owner}</OwnerDiv>
      <LockDiv> {requiresPassword ? 
        <Image src={lock} alt="lock" height={15} width={15}/> : 
        <Image src={unlock} alt="unlock" height={15} width={15} /> }
      </LockDiv>
    </StyledLink>
  );
}

export default RoomLine;