classdef Maze
	properties
        mazedata
    end
    methods
        function m = Maze(d)
            m.mazedata = d;
        end
        function s = getLocation(maze, pos)
            % 1 = up, 2 = right, 3 = down, 4 = left
            x = pos(1);
            y = pos(2);
            s = [0 0 0 0];
            ms = size(maze.mazedata);
            % y\x ---
            % |
            % |
            if x == 1
                % leftmost, left is negative
                s(4) = -1;
            else
                % not leftmost, left is just x-1
                s(4) = maze.mazedata(x-1,y);
            end
            if x == ms(2)
                % rightmost, right is negative
                s(2) = -1;
            else
                % not rightmost, right is just x+1
                s(2) = maze.mazedata(x+1,y);
            end
            
            if y == 1
                % topmost, top is negative
                s(1) = -1;
            else
                % not topmost, top is just y-1
                s(1) = maze.mazedata(x,y-1);
            end
            if y == ms(1)
                % bottommost, bottom is negative
                s(3) = -1;
            else
                % not bottommost, bottom is just y+1
                s(3) = maze.mazedata(x,y+1);
            end
        end
        function a = canMoveHere(maze, pos)
            if maze.mazedata(pos(1), pos(2))
                a = 0;
            else
                a = 1;
            end
        end
    end
end